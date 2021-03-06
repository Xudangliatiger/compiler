#include "Follow.h"

const char* VoidSymbol = "#"; // "ε"
const char* DollarSymbol = "$";

int main(int argc, char* argv[])
{
	//
	// 调用 InitRules 函数初始化文法
	//
	Rule* pHead = InitRules();

	//
	// 初始化 First 集合、Follow 集合
	//
	SetList FirstSetList, FollowSetList;
	FirstSetList.nSetCount = 0;
	FollowSetList.nSetCount = 0;

	//
	// 调用 Follow 函数求文法的 First 集合、Follow 集合
	//
	Follow(pHead, &FollowSetList, &FirstSetList);

	//
	// 输出文法
	//
	PrintRule(pHead);
	
	return 0;
}

/*
功能：
	添加一个 Set 到 SetList。

参数：
	pSetList -- SetList 指针。
	pName -- 集合名称字符串指针。 
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
	// TODO: 在此添加代码
	//
	
}

/*
功能：
	根据名称在 SetList 中查找。

参数：
	pSetList -- SetList 指针。
	pName -- 集合名称字符串指针。
	  
返回值：
	如果找到返回 Set 指针，否则返回 NULL。
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
	// TODO: 在此添加代码
	//
	
}

/*
功能：
	添加一个终结符到 Set。

参数：
	pSet -- Set 指针。
	pTerminal -- 终结符名称指针。
	  
返回值：
	添加成功返回 1，否则返回 0。
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
    else
    { return 0; }	
	//
	// TODO: 在此添加代码
	//
	
}

/*
功能：
	将源 Set 添加到目标 Set 中，忽略ε。

参数：
	pDesSet -- 目标 Set 指针。
	pSrcSet -- 源 Set 指针。
	  
返回值：
	添加成功返回 1，否则返回 0。
*/
int AddSetToSet(Set* pDesSet, const Set* pSrcSet)
{
	int i = 0;
    int j = 0;
    int k = 0;
    for(i = 0; i < (pSrcSet->nTerminalCount)&& strcmp(pSrcSet->Terminal[i],VoidSymbol); i++){
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
	// TODO: 在此添加代码
	//
	
}

/*
功能：
	判断 Set 中是否含有ε。

参数：
	pSet -- Set 指针。
	  
返回值：
	存在返回 1。
	不存在返回 0。
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
	// TODO: 在此添加代码
	//
			
}

/*
功能：
	求文法的 First 集合。

参数：
	pHead -- 文法的头指针。
	pFirstSetList -- First 集合指针。
*/
void First(const Rule* pHead, SetList* pFirstSetList)
{
	const Rule* pRule;  // Rule 指针
	int isChange;	    // 集合是否被修改的标志
	RuleSymbol* pSymbol;// Symbol 游标
	
	//使用文法链表初始化First集合
	for(pRule=pHead;pRule!=NULL;pRule=pRule->pNextRule){
	   AddOneSet(pFirstSetList,pRule->RuleName);
	 }
	 do{
	   		isChange=0;//设置修改标志
	   		for(pRule=pHead;pRule!=NULL;pRule=pRule->pNextRule){
	       		Set *pDesSet=GetSet(pFirstSetList,pRule->RuleName);
	        	int hasVoid=1;//First集合中是否含有e的标志
	        	for(pSymbol=pRule->pFirstSymbol;pSymbol!=NULL&&hasVoid;pSymbol=pSymbol->pNextSymbol){
	                 if(pSymbol->isToken){  
	                         if(AddTerminalToSet(pDesSet,pSymbol->SymbolName))
	                            isChange=1;
	                         hasVoid = 0;// 设置First集合中是否含有e标志
	                  }
	                  else{
	                      //根据非终结符名称在pFirstSetList中查找Set
	                      	Set* pSrcSet= GetSet(pFirstSetList,pSymbol->SymbolName);
	                      	if(AddSetToSet(pDesSet,pSrcSet))
	                            isChange=1;
	                      //调用SetHasVoid函数，判断源Set中是否含有e
	                      	hasVoid=SetHasVoid(pSrcSet);
	                  }   
	           }
	         	if(hasVoid){
	         	//AddTerminalToSet函数将e加入到目标集合中
	         		AddTerminalToSet(pDesSet,VoidSymbol);
	         	}    
	    	}
     }while(isChange);
	//
	// TODO: 在此添加代码
	//
	
}

/*
功能：
	求文法的 Follow 集合。

参数：
	pHead -- 文法的头指针。
	pFollowSetList -- Follow 集合指针。
	pFirstSetList -- First 集合指针。
*/
void Follow(const Rule* pHead, SetList* pFollowSetList, SetList* pFirstSetList)
{
	const Rule* pRule;  // Rule 指针
	int isChange;	    // 集合是否被修改的标志
	RuleSymbol* pSymbol;// Symbol 游标

	// 调用 First 函数求文法的 First 集合
	First(pHead, pFirstSetList);

	// 使用文法链表初始化 Follow 集合
	for(pRule = pHead; pRule != NULL; pRule = pRule->pNextRule)
	{
		AddOneSet(pFollowSetList, pRule->RuleName);
	}

	// 在开始符号的 Follow 集合中加入终结符 $
	AddTerminalToSet(&pFollowSetList->Sets[0], DollarSymbol);

	do
	{
		isChange = 0; // 设置集合修改标志

		for(pRule = pHead; pRule != NULL; pRule = pRule->pNextRule)
		{
			for(pSymbol = pRule->pFirstSymbol; pSymbol != NULL; pSymbol = pSymbol->pNextSymbol)
			{
				// 忽略终结符
				if(pSymbol->isToken)
					continue;

				// 初始化一个 First 集合 TempFirstSet，作为临时变量
				Set TempFirstSet;
				TempFirstSet.nTerminalCount = 0;

				if(NULL != pSymbol->pNextSymbol)
				{
					if(pSymbol->pNextSymbol->isToken) // 终结符
					{
						// 调用 AddTerminalToSet 函数将该终结符加入到 TempFirstSet
						AddTerminalToSet(&TempFirstSet, pSymbol->pNextSymbol->SymbolName);
					}
					else // 非终结符
					{
						// 调用 GetSet 函数在 pFirstSetList 中查找 Set
						Set* pFirstSetXn = GetSet(pFirstSetList, pSymbol->pNextSymbol->SymbolName);

						// 将找到的 Set 加入 TempFirstSet 中
						AddSetToSet(&TempFirstSet, pFirstSetXn);
					}
				}
				else
				{
					// 调用 AddTerminalToSet 函数将 VoidSymbol 加入到 TempFirstSet 中
					AddTerminalToSet(&TempFirstSet, VoidSymbol);
				}

				// 调用 GetSet 函数在 pFollowSetList 中查找 Set
				Set* pFollowSetXi = GetSet(pFollowSetList, pSymbol->SymbolName);

				// 将集合 TempFirstSet 加入 pFollowSetXi
				if(AddSetToSet(pFollowSetXi, &TempFirstSet))
					isChange = 1; // 设置集合修改标志

				if(SetHasVoid(&TempFirstSet)) // 判断集合 TempFirstSet 是否含有ε
				{
					// 调用 GetSet 函数得到当前文法名称对应的 Follow 集合
					Set* pFollowSetA = GetSet(pFollowSetList, pRule->RuleName);

					// 将集合 pFollowSetA 加入 pFollowSetXi
					if(AddSetToSet(pFollowSetXi, pFollowSetA))
						isChange = 1; // 设置集合修改标志
				}
			}
		}

	} while(isChange);
	
	//
	// TODO: 在此添加代码
	//
	
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
功能：
	初始化文法链表。
	
返回值：
	文法的头指针。
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
功能：
	创建一个新的文法。
	
参数：
	pRuleName -- 文法的名字。	
	
返回值：
	文法的指针。
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
功能：
	创建一个新的符号。
	
返回值：
	符号的指针。
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
功能：
	输出文法。
	
参数：
	pHead -- 文法的头指针。
*/
void PrintRule(const Rule* pHead)
{
	const Rule* pRule;
	for(pRule = pHead; pRule != NULL; pRule = pRule->pNextRule)
	{
		printf("%s ->", pRule->RuleName);

		RuleSymbol* pRuleSymbol;
		for(pRuleSymbol = pRule->pFirstSymbol; pRuleSymbol != NULL; pRuleSymbol = pRuleSymbol->pNextSymbol)
		{	
			printf(" %s", pRuleSymbol->SymbolName);
		}
		printf("\n");
	}
}