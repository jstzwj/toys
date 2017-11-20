
def move(states, actions, curState, curAction):
    pos = states[curState]+actions[curAction]
    if pos<0:
        pos=0
    if pos>=len(states):
        pos=len(states)-1
    return pos

# 值迭代异步确定
def qiteration(rewards, states, actions, gamma):
    stateNum=len(states)
    actionNum=len(actions)
    table=[]
    for i in range(0,stateNum):
        table.append([0,0])


    isend=False
    while isend==False:
        isend=True
        print(table)
        for eachState in range(0,stateNum):
            for eachAction in range(0, actionNum):
                nextState= states[eachState]+actions[eachAction]
                if nextState<0 or nextState>=len(states):
                    newval=rewards[eachState][eachAction]
                else:
                    newval=rewards[eachState][eachAction]+gamma*max(table[nextState])

                if eachState==0 or eachState==5:
                    newval=0
                if table[eachState][eachAction]!=newval:
                    isend=False
                table[eachState][eachAction]=newval
        
    return table


# 值迭代异步随机
def qiterationRandom(rewards, states, actions, gamma, probs):
    stateNum=len(states)
    actionNum=len(actions)
    table=[]
    for i in range(0,stateNum):
        table.append([0,0])


    isend=False
    while isend==False:
        isend=True
        print(table)
        for eachState in range(0,stateNum):
            for eachAction in range(0, actionNum):
                newval = 0
                for eachNextState in range(0,stateNum):
                    probNewVal=gamma*max(table[eachNextState])
                    if eachNextState==eachState-1:
                        probNewVal=rewards[eachState][0]+gamma*max(table[eachNextState])
                    if eachNextState==eachState+1:
                        probNewVal=rewards[eachState][1]+gamma*max(table[eachNextState])
                    if eachState==0 or eachState==5:
                        probNewVal=0
                    newval+=probs[eachState][eachAction][eachNextState]*probNewVal
                
                # print("ok")
                if table[eachState][eachAction]!=newval:
                    isend=False
                table[eachState][eachAction]=newval
        
    return table


# 策略迭代异步确定
def policyiteration(rewards, states, actions, gamma):
    stateNum=len(states)
    actionNum=len(actions)
    
    policy=[]
    newpolicy=[]
    for i in range(0,stateNum):
        policy.append(1)
        newpolicy.append(1)

    print("策略：")
    print(policy)
    
    isend=False
    while isend==False:
        isend=True
        isItEnd=False
        
        table=[]
        for i in range(0,stateNum):
            table.append([0,0])
        while isItEnd==False:
            isItEnd=True
            print(table)
            for eachState in range(0,stateNum):
                for eachAction in range(0, actionNum):
                    nextState= states[eachState]+actions[eachAction]
                    if nextState<0 or nextState>=len(states):
                        newval=rewards[eachState][eachAction]
                    else:
                        newval=rewards[eachState][eachAction]+gamma*table[nextState][policy[nextState]]

                    if eachState==0 or eachState==5:
                        newval=0
                    
                    if table[eachState][eachAction]!=newval:
                        isItEnd=False
                    table[eachState][eachAction]=newval
        # 更新policy
        for eachState in range(0,stateNum):
            if table[eachState][0]<table[eachState][1]:
                newpolicy[eachState]=1
            else:
                newpolicy[eachState]=0

        print("策略：")
        print(policy)
        
        if policy!=newpolicy:
            isend=False
        policy=newpolicy
    return table


# 策略迭代异步随机
def policyiterationRandom(rewards, states, actions, gamma, probs):
    stateNum=len(states)
    actionNum=len(actions)
    
    policy=[]
    newpolicy=[]
    for i in range(0,stateNum):
        policy.append(1)
        newpolicy.append(1)

    print("策略：")
    print(policy)
    
    isend=False
    while isend==False:
        isend=True
        isItEnd=False
        
        table=[]
        for i in range(0,stateNum):
            table.append([0,0])
        while isItEnd==False:
            isItEnd=True
            print(table)
            for eachState in range(0,stateNum):
                for eachAction in range(0, actionNum):
                    newval = 0
                    for eachNextState in range(0,stateNum):
                        probNewVal=gamma*table[eachNextState][policy[eachNextState]]
                        if eachNextState==eachState-1:
                            probNewVal=rewards[eachState][0]+gamma*table[eachNextState][policy[eachNextState]]
                        if eachNextState==eachState+1:
                            probNewVal=rewards[eachState][1]+gamma*table[eachNextState][policy[eachNextState]]
                        if eachState==0 or eachState==5:
                            probNewVal=0
                        newval+=probs[eachState][eachAction][eachNextState]*probNewVal

                        if eachState==0 or eachState==5:
                            newval=0
                    
                    if table[eachState][eachAction]!=newval:
                        isItEnd=False
                    table[eachState][eachAction]=newval
        # 更新policy
        for eachState in range(0,stateNum):
            if table[eachState][0]<table[eachState][1]:
                newpolicy[eachState]=1
            else:
                newpolicy[eachState]=0

        print("策略：")
        print(policy)
        
        if policy!=newpolicy:
            isend=False
        policy=newpolicy
    return table



print("异步值迭代确定")
print(qiteration([[0,0],[1,0],[0,0],[0,0],[0,5],[0,0]],[0,1,2,3,4,5],[-1,1],0.5))


print("异步值迭代随机")
print(qiterationRandom([[0,0],[1,0],[0,0],[0,0],[0,5],[0,0]],[0,1,2,3,4,5],[-1,1],0.5,[[[0.15,0.05,0,0,0,0],[0.15,0.8,0,0,0,0]]
                                                                                       ,[[0.8,0.15,0.05,0,0,0],[0.05,0.15,0.8,0,0,0]]
                                                                                       ,[[0,0.8,0.15,0.05,0,0],[0,0.05,0.15,0.8,0,0]]
                                                                                       ,[[0,0,0.8,0.15,0.05,0],[0,0,0.05,0.15,0.8,0]]
                                                                                       ,[[0,0,0,0.8,0.15,0.05],[0,0,0,0.05,0.15,0.8]]
                                                                                       ,[[0,0,0,0,0.8,0.15],[0,0,0,0,0.05,0.15]]]))

print("策略迭代异步确定")
print(policyiteration([[0,0],[1,0],[0,0],[0,0],[0,5],[0,0]],[0,1,2,3,4,5],[-1,1],0.5))

print("策略迭代异步随机")
print(policyiterationRandom([[0,0],[1,0],[0,0],[0,0],[0,5],[0,0]],[0,1,2,3,4,5],[-1,1],0.5,[[[0.15,0.05,0,0,0,0],[0.15,0.8,0,0,0,0]]
                                                                                       ,[[0.8,0.15,0.05,0,0,0],[0.05,0.15,0.8,0,0,0]]
                                                                                       ,[[0,0.8,0.15,0.05,0,0],[0,0.05,0.15,0.8,0,0]]
                                                                                       ,[[0,0,0.8,0.15,0.05,0],[0,0,0.05,0.15,0.8,0]]
                                                                                       ,[[0,0,0,0.8,0.15,0.05],[0,0,0,0.05,0.15,0.8]]
                                                                                       ,[[0,0,0,0,0.8,0.15],[0,0,0,0,0.05,0.15]]]))


    
