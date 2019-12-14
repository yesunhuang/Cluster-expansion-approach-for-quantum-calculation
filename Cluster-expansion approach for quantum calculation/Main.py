import numpy as np
import queue
from scipy import *

class OPM:
    "Operator Normalize"
    def __init__(self, Operator):
        "initialize class"
        if (len(Operator)>0):
            OpN=int(2<<(len(Operator)-1))+int(Operator,2)
        else:
            OpN=0
        #We put a '1' at the front to denote the operator's digits
        self.N=int(((len(Operator)+2)*(len(Operator)+1)/2)-1)+1
        self.Cof=np.zeros(self.N)
        print(OpN)
        print("Operator present in calculation: "+bin(OpN)[2:])
        print("This operator is normalize? "+str(self.isNormalized(OpN)))
        self.NormalizeOperator(OpN)
    
    def hash(self,Operator):
        "return the hash code"
        n=int(floor(log2(Operator)))
        m=int(floor(log2(Operator-(1<<n)+1)))
        return (int((n+1)*n/2+m),m)

    def invHash(self,hashcode):
        "return the operator"
        n=int(floor((-1+sqrt(1+8*hashcode))/2))
        m=int(hashcode-(n+1)*n/2)
        if (m>0):
            return(int((1<<n)+(1<<m)-1),int(m))
        else:
            return(int(1<<n),0)

    def isNormalized(self,Operator):
        "Check if it is normalized"
        n=floor(log2(Operator))
        Zero=False; isNormalized=True;
        while(n>0):
            code=Operator & 1
            Operator=Operator>>1
            if(code==0):
                Zero=True;
            if((Zero==True)and(code==1)):
                isNormalized=False;
            n=n-1;
        return isNormalized

    def NormalizeOperator(self,Operator):
        "doing the Normalize process"
        OperatorQue=queue.Queue()
        n=int(floor(log2(Operator)));m=0
        while(Operator & 1==1):
            m=m+1
            Operator=Operator>>1
        if(m==n+1):
            m=m-1
        (hashcode,m)=self.hash((1<<(m+1))-1)
        OperatorQue.put(hashcode)
        self.Cof[hashcode]=1
        lastOne=m
        for i in range(m+1,n+1):
            inque=np.zeros(self.N,dtype=bool)
            code=Operator & 1;Operator=Operator >> 1;
            if(code==0):
                continue;
            QueN=OperatorQue.qsize()
            leftZero=i-lastOne-1
            while(QueN>0):
                QueN-=1
                subHash=OperatorQue.get()
                subCof=self.Cof[subHash]; self.Cof[subHash]=0;
                (subOperator,subm)=self.invHash(subHash)
                subn=int(floor(log2(subOperator)))
                i0=leftZero+subn+1
                Op1=subOperator-(1<<subn)+(1<<i0)+(1<<subm)
                (Sh1,Sb1)=self.hash(Op1)
                self.Cof[Sh1]+=subCof
                if (inque[Sh1]==False):
                    OperatorQue.put(Sh1)
                    inque[Sh1]=True
                if((i0-2<0)or(i0-subm-1<=0)):
                    continue;
                Op2=subOperator-(1<<subn)+(1<<(i0-2))
                (Sh2,Sb2)=self.hash(Op2)
                self.Cof[Sh2]+=(i0-subm-1)*subCof
                if (inque[Sh2]==False):
                    OperatorQue.put(Sh2)
                    inque[Sh2]=True
                
            lastOne=i;
        leftZero=n-lastOne
        QueN=OperatorQue.qsize()
        while((QueN>0)and(leftZero>0)):
            QueN-=1
            subHash=OperatorQue.get()
            subCof=self.Cof[subHash]; self.Cof[subHash]=0;
            (subOperator,subm)=self.invHash(subHash)
            subn=int(floor(log2(subOperator)))
            Op=subOperator-(1<<subn)+(1<<subn+leftZero)
            (Sh,Sb)=self.hash(Op)
            self.Cof[Sh]=subCof
            OperatorQue.put(Sh)
        self.printResult(OperatorQue)
        return(OperatorQue)

    def printResult(self,OPQue):
        queN=OPQue.qsize()
        while(queN>0):
            queN-=1
            subHash=OPQue.get()
            (subOperator,subm)=self.invHash(subHash)
            print(bin(subOperator)[3:]+" "+str(self.Cof[subHash])[0:-2])
       
