<!DOCTYPE html>
<html lang="zh-cn">

<head>
<meta charset="utf-8" />
<meta name="robots" content="all" />
<meta name="author" content="w3school.com.cn" />



</head>




<body>
<canvas id="myCanvas" width="500" height="500"></canvas>



</body>

<script type="text/javascript">


  var canvas = document.getElementById("myCanvas");
  var context = canvas.getContext("2d");
  var interal = setInterval(function () { step();},50);


  var w=13;
  var h=13;
  var interval=25.0;
  //整体偏移
  var offX=50,offY=50;
  //存储光标位置
  var cursorX,cursorY;
  //哪一方执子
  var whichTurn=1;//1=黑方，2=白方
  //存储棋盘
  var chessBoard=new Array(h);
  //初始化
  for(var i=0;i<h;++i)
  {
    chessBoard[i]=new Array(w);
    for(var j=0;j<w;++j)
    {
      chessBoard[i][j]=0;//1=黑棋，2=白棋
    }
  }

  function drawLines()
  {
    context.strokeStyle = "rgb(0,0,0)";
    context.fillStyle = "rgb(255,255,255)";

    context.beginPath();
    for(var i=0;i<h-1;++i)
    {
      context.moveTo(offX+interval*i, offY+0);
      context.lineTo(offX+interval*i,offY+interval*(h-1));
    }
    for(var i=0;i<w-1;++i)
    {
      context.moveTo(offX+0, offY+interval*i);
      context.lineTo(offX+interval*(w-1),offY+interval*i);
    }

    context.stroke();
    //context.fill();
  }
  function drawOutLines()
  {
    context.strokeStyle = "rgb(0,0,0)";
    context.fillStyle = "rgb(255,255,255)";

    context.beginPath();
    context.moveTo(offX+0, offY+0);
    context.lineTo(offX+interval*(w-1),offY+0);
    context.lineTo(offX+interval*(w-1),offY+interval*(h-1));
    context.lineTo(offX+0,offY+interval*(h-1));
    context.lineTo(offX+0,offY+0);

    context.stroke();
    //context.fill();
  }
  function drawPointsOnBoard()
  {
    context.strokeStyle = "rgb(0,0,0)";
    context.fillStyle = "rgb(0,0,0)";
    context.beginPath();
    context.arc(offX+interval*(parseInt(w/2)),offY+interval*(parseInt(h/2)),3,0,Math.PI*2,true);
    context.closePath();

    //context.stroke();
    context.fill();
  }

  function drawAChess(in_w,in_h,in_color)
  {
    context.strokeStyle = "rgb(0,0,0)";
    context.fillStyle = in_color;

    //外框
    context.beginPath();
    context.arc(in_w,in_h,6,0,Math.PI*2,true);
    context.closePath();

    context.fill();
    context.stroke();
    //高光
    //TODO
  }
  function drawChesses()
  {
    for(var i=0;i<h;++i)
    {
      for(var j=0;j<w;++j)
      {
        if(chessBoard[i][j]==1)
        {
          drawAChess(offX+interval*j,offY+interval*i,"rgb(0,0,0)");
        }
        else if(chessBoard[i][j]==2)
        {
          drawAChess(offX+interval*j,offY+interval*i,"rgb(250,250,250)");
        }
      }
    }

  }
  //换手
  function turnSwap()
  {
    if(whichTurn==1)
    {
      whichTurn=2;
    }
    else
    {
      whichTurn=1;
    }
  }
  //判断一个点是否越界
  function judgeOverRange(in_w,in_h)
  {
    return !(in_w>=0&&in_w<w&&in_h>=0&&in_h<h);
  }
  //谁赢？
  function judgeWhoWin(in_w,in_h)
  {
    //数字表示方向
    //从x轴正向逆时针旋转，例如0,45,90,135,180,225...
    var sum=[0,0,0,0,0,0,0,0];
    var dircos=[1,1,0,-1,-1,-1,0,1];
    var dirsin=[0,1,1,1,0,-1,-1,-1];
    for(var degree=0;degree<360;degree+=45)
    {
      for(var i=1;i<=4;++i)
      {
        var neww=in_w+dircos[degree/45]*i;
        var newh=in_h-dirsin[degree/45]*i;
        if(judgeOverRange(neww,newh)==false&&chessBoard[newh][neww]==whichTurn)
        {
          sum[parseInt(degree/45)]++;
        }
        else
        {
          break;
        }
      }
    }
    for(var i=0;i<4;++i)
    {
      if(sum[i]+sum[i+4]>=4)
      {
        if(whichTurn==1)
        {
          alert("黑方获胜");
        }
        else
        {
          alert("白方获胜");
        }
        return true;
      }
    }
    return false;
  }
  function restart()
  {
    for(var i=0;i<h;++i)
    {
      for(var j=0;j<w;++j)
      {
        chessBoard[i][j]=0;
      }
    }
  }
  function step()
  {
    //清屏
    context.clearRect(0, 0, canvas.width, canvas.height);
    //绘制棋盘
    drawOutLines();
    drawLines();
    drawPointsOnBoard();
    //绘制棋盘上的棋子
    drawChesses();
    //绘制手上的棋子
    if(whichTurn==1)
      drawAChess(cursorX, cursorY,"rgb(0,0,0)");
    else
      drawAChess(cursorX, cursorY,"rgb(250,250,250)");

  }

  canvas.onmousemove=function(e)
  {
    cursorX=e.layerX;
    cursorY=e.layerY;
  }
  canvas.onclick=function(e)
  {
    if(cursorX-offX>=0&&cursorX-offX<=interval*(w-1)&&cursorY-offY>=0&&cursorY-offY<=interval*(h-1))
    {
      if(chessBoard[parseInt((cursorY-offY)/interval+0.5)][parseInt((cursorX-offX)/interval+0.5)]==0)
      {
        chessBoard[parseInt((cursorY-offY)/interval+0.5)][parseInt((cursorX-offX)/interval+0.5)]=whichTurn;
        //判断输赢
        if(judgeWhoWin(parseInt((cursorX-offX)/interval+0.5),parseInt((cursorY-offY)/interval+0.5))==true)
        {
          restart();
        }
        //换手
        turnSwap();
      }

    }
    else
    {
      //alert();
      //当心越界
    }
  }


</script>


</html>
