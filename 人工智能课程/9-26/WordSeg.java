package wordseg;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.FileReader;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.util.ArrayList;
import java.util.HashSet;

class Dictionary{
	public HashSet<String> dict;
	public int maxLen;
	public Dictionary(){
		dict=new HashSet<String>();
	}
	
	public void add(String str){
		dict.add(str);
	}
	
	public boolean find(String str){
		return dict.contains(str);
	}
}

public class WordSeg {
	/*
	 * ���ļ��ж����ֵ�
	 */
	public static Dictionary readDictFromFile(String path){
		Dictionary result=new Dictionary();
		int num = 0;
		try {
			InputStreamReader isr = new InputStreamReader(new FileInputStream(path), "UTF-8");
			BufferedReader br = new BufferedReader(isr); 
			
	    	// read file content from file 
	           
	    	String str = null;
	    	
	    	if((str = br.readLine()) != null){
	    		String[] tmp=str.split("\t|\n");
	    		num=Integer.parseInt(tmp[0]);
	    		result.maxLen=Integer.parseInt(tmp[1]);
	    	}
	           
	    	int i = 0;
	    	while((str = br.readLine()) != null && i<num) {
	    		result.add(str);
	    		++i;
	        }
	           
	        br.close();
	        isr.close();
	      }catch(Exception e) {
	      		e.printStackTrace();
	      }
		 return result;
	}
	
	/*
	 * ���ļ��ж�����Ҫ������ı�
	 */
	public static String readTextFromFile(String path){
		StringBuffer sb= new StringBuffer("");
		try {
            // read file content from file
			InputStreamReader isr = new InputStreamReader(new FileInputStream(path), "UTF-8");
			BufferedReader br = new BufferedReader(isr); 
           
            String str = null;
           
            while((str = br.readLine()) != null) {
                  sb.append(str+"\n");
            }
           
            br.close();
            isr.close();
	    }catch(Exception e) {
	    	e.printStackTrace();
	    } 
		return sb.toString();
	}
	
	/*
	 * �ִ�
	 */
	public static ArrayList<String> seg(Dictionary dict,String text){
		String[] sentence=text.split("\n");
		ArrayList<String> result=new ArrayList<String>();
		for(String eachLine:sentence)
		{
			int pos=0;
			while(pos<eachLine.length())
			{
				// һ�����������Ϊ10
				for(int i=10;i>=1;--i)
				{
					if(pos+i<=eachLine.length())
					{
						// ��������ʽ�ȡ����
						String tmpWord=eachLine.substring(pos, pos+i);
						// System.out.println(tmpWord);
						if(i==1||dict.find(tmpWord))
						{
							result.add(tmpWord);
							pos+=i;
							break;
						}
					}
				}
			}
			result.add("\n");
		}
		
		return result;
	}
	
	/*
	 * �����д���ļ�
	 */
	public static void writeToFile(String path,ArrayList<String> result)
	{
		try {
			OutputStreamWriter isr = new OutputStreamWriter(new FileOutputStream(path), "UTF-8");
			BufferedWriter br = new BufferedWriter(isr); 
           
			for(String each:result)
			{
				br.write(each+" ");
			}
           
            br.close();
            isr.close();
	    }catch(Exception e) {
	    	e.printStackTrace();
	    } 
	}
	
	/*
	 * ���ļ��ж�����
	 */
	public static ArrayList<String> readAnsFromFile(String path)
	{
		ArrayList<String> result=new ArrayList<String>();
		try {
			InputStreamReader isr = new InputStreamReader(new FileInputStream(path), "UTF-8");
			BufferedReader br = new BufferedReader(isr); 
			
	    	// read file content from file 
	    	String str = null;
	           
	    	while((str = br.readLine()) != null) {
	    		String[] line=str.split(" ");
	    		for(String each:line)
	    		{
	    			result.add(each);
	    		}
	    		result.add("\n");
	        }
	           
	        br.close();
	        isr.close();
	      }catch(Exception e) {
	      		e.printStackTrace();
	      }
		 return result;
	}
	
	/*
	 * ������ȷ�ĵ�����
	 */
	public static int rightWord(ArrayList<String> result,ArrayList<String> answer)
	{
		int numleft=0;
		int ileft=0;
		int numright=0;
		int iright=0;
		int num=0;
		while(ileft<result.size()&&iright<answer.size())
		{
			String lft = result.get(ileft);
			String rght = answer.get(iright);
			if(lft.equals(rght) &&
					!lft.contains("\n") &&
					!rght.contains("\n"))
			{
				++num;
			}
			
			if(numleft>numright)
			{
				numright += answer.get(iright).length();
				iright++;
			}
			else if(numleft<numright)
			{
				numleft += result.get(ileft).length();
				ileft++;
			}
			else
			{
				numleft += result.get(ileft).length();
				ileft++;
				numright += answer.get(iright).length();
				iright++;
			}
		}
		if(numleft!=numright)
		{
			System.out.println("�������ֲ�һ����");
			return 0;
		}
		else
		{
			return num;
		}
	}
	
	
	public static void main(String[] args) {
		// ���ļ��ж����ֵ�
		Dictionary dict=readDictFromFile("corpus.dict.txt");
		// ���ļ��ж����ı�
		String text=readTextFromFile("corpus.sentence.txt");
		// �ִ�
		ArrayList<String> result=seg(dict,text);
		// ���ļ��ж�����
		ArrayList<String> answer=readAnsFromFile("corpus.answer.txt");
		
		// ������ȷ�ĵ�����
		int rightWord=rightWord(result,answer);
		
		// ����
		double Precision=(double)rightWord/result.size();
		double Recall=(double)rightWord/answer.size();
		double f=Precision*Recall*2/(Precision+Recall);
		
		// ���P/R/Fָ��
		System.out.println("Precision="+rightWord+"/"+result.size()+"="+Precision);
		System.out.println("Recall="+rightWord+"/"+answer.size()+"="+Recall);
		System.out.println("f="+Precision+"*"+Recall+"*2"+"/("+Precision+"+"+Recall+")="+f);
		
		// д��𰸵��ļ�
		writeToFile("corpus.out.txt",result);
		
	}

}
