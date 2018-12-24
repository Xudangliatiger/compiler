#include "First.h"

const char* VoidSymbol = "$"; // "��"

int main(int argc, char* argv[])
{
	//
	// ���� InitRules ������ʼ���ķ�
	//
	Rule* pHead = InitRules();
	
	//
	// ����ķ�
	//
	PrintRule(pHead);
	
	//
	// ���� First �������ķ��� First ����
	//
	SetList FirstSet;
	FirstSet.nSetCount = 0;
	First(pHead, &FirstSet);

	return 0;
}

/*
���ܣ�
	���һ�� Set �� SetList��

������
	pSetList -- SetList ָ�롣
	pName -- ���������ַ���ָ�롣 
*/
void AddOneSet(SetList* pSetList, const char* pName)
{
	int i;
    for(i = 0; i < pSetList->nSetCount; i++){
    	if(!strcmp(pSetList->Sets[i].Name, pName))
    	break;
   }
   if(i == pSetList->nSetCount){
    	strcpy(pSetList->Sets[pSetList->nSetCount].Name, pName);
    	pSetList->nSetCount++;  
   }
	//
	// TODO: �ڴ���Ӵ���
	//
	
}
/*
���ܣ�
	���������� SetList �в��� Set��

������
	pSetList -- SetList ָ�롣
	pName -- ���������ַ���ָ�롣
	  
����ֵ��
	����ҵ����� Set ��ָ�룬���򷵻� NULL��
*/
Set* GetSet(SetList* pSetList, const char* pName)
{
	Set* SetCursor = (Set*)malloc(sizeof(Set));
    int i = 0;
    for(*SetCursor = pSetList->Sets[0]; i < pSetList->nSetCount; i++){
      *SetCursor = pSetList->Sets[i];
      if(!strcmp(SetCursor->Name, pName)){
      	 return &pSetList->Sets[i];
      }
    } 
    return NULL;
	//
	// TODO: �ڴ���Ӵ���
	//
	
}

/*
���ܣ�
	���һ���ս���� Set��

������
	pSet -- Set ָ�롣
	pTerminal -- �ս������ָ�롣
	  
����ֵ��
	��ӳɹ����� 1��
	��Ӳ��ɹ����� 0��
*/
int AddTerminalToSet(Set* pSet, const char* pTerminal)
{
	int i = 0; 
    for(i = 0; i < pSet->nTerminalCount; i++){
    	if(!strcmp(pSet->Terminal[i], pTerminal))
   	 	break;
    	else
    	continue;
    }
    if(i == pSet->nTerminalCount){
   	 strcpy(pSet->Terminal[pSet->nTerminalCount], pTerminal);
   	 pSet->nTerminalCount++;
   	 return 1;
    }
    else{
   	 return 0; 
    }	
}

/*
���ܣ�
	��Դ Set �е������ս����ӵ�Ŀ�� Set �С�

������
	pDesSet -- Ŀ�� Set ָ�롣
	pSrcSet -- Դ Set ָ�롣
	  
����ֵ��
	��ӳɹ����� 1�����򷵻� 0��
*/
int AddSetToSet(Set* pDesSet, const Set* pSrcSet)
{
	int i = 0;
    int j = 0;
    int k = 0;
    for(i = 0; i < (pSrcSet->nTerminalCount); i++){
   	 for(j = 0; j < pDesSet->nTerminalCount; j++){
      	 if(!strcmp(pSrcSet->Terminal[i],pDesSet->Terminal[j]))
      	 break;
   	 }
     if(j == pDesSet->nTerminalCount){
      	if(!strcpy(pDesSet->Terminal[pDesSet->nTerminalCount],pSrcSet->Terminal[i]))
      	return 0;
      	pDesSet->nTerminalCount++;
      	k++;
  	 }
   }
    if(k == 0)
 	return 0;
 	else
 	return 1;
	//
	// TODO: �ڴ���Ӵ���
	//
	
}


/*
���ܣ�
	�ж� Set ���ս�����Ƿ��Цš�

������
	pSet -- Set ָ�롣
	  
����ֵ��
	���ڷ��� 1��
	�����ڷ��� 0��
*/
int SetHasVoid(const Set* pSet)
{
	int i = 0;
    for(i = 0; i < pSet->nTerminalCount; i++)
    {
    	if(!strcmp(pSet->Terminal[i], VoidSymbol))
    	return 1;
    }
    return 0;		
	//
	// TODO: �ڴ���Ӵ���
	//			
}


/*
���ܣ�
	���ķ��� First ���ϡ�

������
	pHead -- �ķ���ͷָ�롣
	pFirstSetList -- First ����ָ�롣
*/
void First(const Rule* pHead, SetList* pFirstSetList)
{
	const Rule* pRule;  // Rule ָ��
	int isChange;	    // �����Ƿ��޸ĵı�־
	RuleSymbol* pSymbol;// Symbol �α�


	//
	// TODO: �ڴ���Ӵ���
	//
	for(pRule=pHead;pRule!=NULL;pRule=pRule->pNextRule){
	   AddOneSet(pFirstSetList,pRule->RuleName);
	 }
	 do{
	   		isChange=0;//�����޸ı�־
	   		for(pRule=pHead;pRule!=NULL;pRule=pRule->pNextRule){
	       		Set *pDesSet=GetSet(pFirstSetList,pRule->RuleName);
	        	int hasVoid=1;//First�������Ƿ���e�ı�־
	        	for(pSymbol=pRule->pFirstSymbol;pSymbol!=NULL&&hasVoid;pSymbol=pSymbol->pNextSymbol){
	                 if(pSymbol->isToken){  
	                         if(AddTerminalToSet(pDesSet,pSymbol->SymbolName))
	                            isChange=1;
	                         hasVoid = 0;// ����First�������Ƿ���e��־
	                  }
	                  else{
	                      //���ݷ��ս��������pFirstSetList�в���Set
	                      	Set* pSrcSet= GetSet(pFirstSetList,pSymbol->SymbolName);
	                      	if(AddSetToSet(pDesSet,pSrcSet))
	                            isChange=1;
	                      //����SetHasVoid�������ж�ԴSet���Ƿ���e
	                      	hasVoid=SetHasVoid(pSrcSet);
	                  }   
	           }
	         	if(hasVoid){
	         	//AddTerminalToSet������e���뵽Ŀ�꼯����
	         		AddTerminalToSet(pDesSet,VoidSymbol);
	         	}    
	    	}
     }while(isChange);
	
}

typedef struct _SYMBOL{
	int isToken;
	char SymbolName[MAX_STR_LENGTH];
}SYMBOL;

typedef struct _RULE_ENTRY{
	char RuleName[MAX_STR_LENGTH];
	SYMBOL Symbols[64];
}RULE_ENTRY;

static const RULE_ENTRY rule_table[] =
{
	/* exp -> exp addop term| term */
	{ "exp", { { 0, "exp" }, { 0, "addop"}, { 0, "term"} } },
	{ "exp", { { 0, "term" } } },

	/* addop -> + | - */
	{ "addop", { { 1, "+" } } },
	{ "addop", { { 1, "-" } } },

	/* term -> term mulop factor | factor */
	{ "term", { { 0, "term" }, { 0, "mulop"}, { 0, "factor"} } },
	{ "term", { { 0, "factor" } } },

	/* mulop -> * */
	{ "mulop", { { 1, "*" } } },

	/* factor -> (exp) | number */
	{ "factor", { { 1, "(" }, { 0, "exp"}, { 1, ")"} } },
	{ "factor", { { 1, "number" } } },
};

/*
���ܣ�
	��ʼ���ķ�����
	
����ֵ��
	�ķ���ͷָ�롣
*/
Rule* InitRules()
{
	Rule *pHead, *pRule;
	RuleSymbol **pSymbolPtr, *pNewSymbol;
	int nRuleCount = sizeof(rule_table) / sizeof(rule_table[0]);
	int i, j;

	Rule** pRulePtr = &pHead;
	for(i=0; i<nRuleCount; i++)
	{
		*pRulePtr = CreateRule(rule_table[i].RuleName);
		pRulePtr = &(*pRulePtr)->pNextRule;
	}

	pRule = pHead;
	for(i=0; i<nRuleCount; i++)
	{
		pSymbolPtr = &pRule->pFirstSymbol;
		for(j=0; rule_table[i].Symbols[j].SymbolName[0] != '\0'; j++)
		{
			const SYMBOL* pSymbol = &rule_table[i].Symbols[j];

			pNewSymbol = CreateSymbol();
			pNewSymbol->isToken = pSymbol->isToken;
			strcpy(pNewSymbol->SymbolName, pSymbol->SymbolName);
			*pSymbolPtr = pNewSymbol;

			pSymbolPtr = &pNewSymbol->pNextSymbol;
		}

		pRule = pRule->pNextRule;
	}

	return pHead;
}

/*
���ܣ�
	����һ���µ��ķ���
	
������
	pRuleName -- �ķ������֡�	
	
����ֵ��
	�ķ���ָ�롣
*/
Rule* CreateRule(const char* pRuleName)
{
	Rule* pRule = (Rule*)malloc(sizeof(Rule));

	strcpy(pRule->RuleName, pRuleName);
	pRule->pFirstSymbol = NULL;
	pRule->pNextRule = NULL;

	return pRule;
}

/*
���ܣ�
	����һ���µķ��š�
	
����ֵ��
	���ŵ�ָ�롣
*/
RuleSymbol* CreateSymbol()
{
	RuleSymbol* pSymbol = (RuleSymbol*)malloc(sizeof(RuleSymbol));

	pSymbol->pNextSymbol = NULL;
	pSymbol->isToken = -1;
	pSymbol->SymbolName[0] = '\0';

	return pSymbol;
}

/*
���ܣ�
	����ķ���
	
������
	pHead -- �ķ���ͷָ�롣
*/
void PrintRule(const Rule* pHead)
{
	const Rule* pRule;
	for(pRule = pHead; pRule != NULL; pRule = pRule->pNextRule){
		printf("%s ->", pRule->RuleName);
		RuleSymbol* pRuleSymbol;
		for(pRuleSymbol = pRule->pFirstSymbol; pRuleSymbol != NULL; pRuleSymbol = pRuleSymbol->pNextSymbol){	
			printf(" %s", pRuleSymbol->SymbolName);
		}
		printf("\n");
	}
	//
	// TODO: �ڴ���Ӵ���
	//

}