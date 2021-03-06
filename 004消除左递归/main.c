#include "RemoveLeftRecursion.h"

const char* VoidSymbol = "$"; // "ε"
const char* Postfix = "'";


int main(int argc, char* argv[])
{
	//
	// 调用 InitRules 函数初始化文法
	//
	Rule* pHead = InitRules();

	//
	// 输出消除左递归之前的文法
	//
	printf("Before Remove Left Recursion:\n");
	PrintRule(pHead);

	// 
	// 调用 RemoveLeftRecursion 函数对文法消除左递归
	//
	RemoveLeftRecursion(pHead);
	
	//
	// 输出消除左递归之后的文法
	//
	printf("\nAfter Remove Left Recursion:\n");
	PrintRule(pHead);
	
	return 0;
}

/*
功能：
	将一个 Symbol 添加到 Select 的末尾。

参数：
	pSelect -- Select 指针。
	pNewSymbol -- Symbol 指针。
*/
void AddSymbolToSelect(RuleSymbol* pSelect, RuleSymbol* pNewSymbol)
{
	 
	while (pSelect->pNextSymbol != NULL){
		pSelect= pSelect->pNextSymbol;
	}
	pSelect->pNextSymbol = pNewSymbol;	
}

/*
功能：
	将一个 Select 加入到文法末尾。当 Select 为 NULL 时就将一个ε终结符加入到文法末尾。

参数：
	pRule -- 文法指针。
	pNewSelect -- Select 指针。
*/
void AddSelectToRule(Rule* pRule, RuleSymbol* pNewSelect)
{
	RuleSymbol* pSelectTemp;
	pSelectTemp = pRule->pFirstSymbol;
	//文法当前无任何规则时
	if(pSelectTemp == NULL){
		//当 Select 为 NULL 时就将一个ε终结符加入到文法末尾
		if(pNewSelect == NULL){
			pRule->pFirstSymbol = CreateSymbol();
			pRule->pFirstSymbol->isToken = 1;
			strcpy(pRule->pFirstSymbol->TokenName, "$");
		}
		else{
			pRule->pFirstSymbol = pNewSelect;
		}
	}
	else{
		//select指针移到当前文法最后一个select
		while(pSelectTemp->pOther != NULL){
			pSelectTemp = pSelectTemp->pOther;
		}
		if(pNewSelect == NULL){
			pSelectTemp->pOther = CreateSymbol();
			pSelectTemp->pOther->isToken = 1;
			strcpy(pSelectTemp->pOther->TokenName, "$");
		}
		else{
			pSelectTemp->pOther = pNewSelect;
		}
	}
}

/*
功能：
	消除左递归。

参数：
	pHead -- 文法链表的头指针。
*/
void RemoveLeftRecursion(Rule* pHead)
{
	RuleSymbol* pSelect;	// Select 游标;
	Rule* pNewRule;			// Rule 指针;

	pNewRule = CreateRule(pHead->RuleName); // 创建新 Rule
	strcat(pNewRule->RuleName, Postfix);

	pSelect = pHead->pFirstSymbol; // 初始化 Select 游标
	RuleSymbol **pSelectPrePtr = &pHead->pFirstSymbol;
	
	while(pSelect != NULL) // 循环处理所有的 Select
	{
		if(0 == pSelect->isToken && pSelect->pRule == pHead)// Select 存在左递归
		{	
			//移除包含左递归的 Select
		
			RuleSymbol* a = pSelect->pNextSymbol;
			RuleSymbol* b = CreateSymbol();
			b->isToken = 0;
			b->pRule = pNewRule;
			AddSymbolToSelect(a, b);
			AddSelectToRule(pNewRule,a);
			

			(*pSelectPrePtr) =  (*pSelectPrePtr)->pOther;
			
			//把所有的有A->A的情况全部给删除了。。 
			
			//移除包含左递归的 Select，将其转换为右递归后添加到新 Rule 的末尾，并移动游标
			
			pSelect=pSelect->pOther;
			
		}
		else // Select 不存在左递归
		{
			//在没有左递归的 Select 末尾添加指向新 Rule 的非终结符，并移动游标
			RuleSymbol* b = CreateSymbol();
			b->isToken = 0;
			b->pRule = pNewRule;
			AddSymbolToSelect(pSelect,b);
			
			pSelectPrePtr = &((*pSelectPrePtr)->pOther);
			pSelect=pSelect->pOther;
		}
		
		

		
	}

	//在新 Rule 的最后加入ε(用 '$' 代替)
	
	AddSelectToRule(pNewRule, NULL);



	
	//将新 Rule 插入文法链表
	pHead->pNextRule = pNewRule;
	
	
	return pHead;
}


/*
功能：
	使用给定的数据初始化文法链表

返回值：
	Rule 指针
*/
typedef struct _SYMBOL{
	int isToken;
	char Name[MAX_STR_LENGTH];
}SYMBOL;

typedef struct _RULE_ENTRY{
	char RuleName[MAX_STR_LENGTH];
	SYMBOL Selects[64][64];
}RULE_ENTRY;

static const RULE_ENTRY rule_table[] =
{
	/* A -> Aa | bA | c | Ad */
	{ "A", {
				{ { 0, "A" }, { 1, "a" } },
				{ { 1, "b" }, { 0, "A" } },
				{ { 1, "c" } },
				{ { 0, "A" }, { 1, "d" } }
			}
	}
};

Rule* InitRules()
{
	Rule *pHead, *pRule;
	RuleSymbol **pSymbolPtr1, **pSymbolPtr2;
	int nRuleCount = sizeof(rule_table) / sizeof(rule_table[0]);
	int i, j, k;

	Rule** pRulePtr = &pHead;
	for(i=0; i<nRuleCount; i++)
	{
		*pRulePtr = CreateRule(rule_table[i].RuleName);
		pRulePtr = &(*pRulePtr)->pNextRule;
	}

	pRule = pHead;
	for(i=0; i<nRuleCount; i++)
	{
		pSymbolPtr1 = &pRule->pFirstSymbol;
		for(j=0; rule_table[i].Selects[j][0].Name[0] != '\0'; j++)
		{
			pSymbolPtr2 = pSymbolPtr1;
			for(k=0; rule_table[i].Selects[j][k].Name[0] != '\0'; k++)
			{
				const SYMBOL* pSymbol = &rule_table[i].Selects[j][k];

				*pSymbolPtr2 = CreateSymbol();
				(*pSymbolPtr2)->isToken = pSymbol->isToken;
				if(1 == pSymbol->isToken)
				{
					strcpy((*pSymbolPtr2)->TokenName, pSymbol->Name);
				}
				else
				{
					(*pSymbolPtr2)->pRule = FindRule(pHead, pSymbol->Name);
					if(NULL == (*pSymbolPtr2)->pRule)
					{
						printf("Init rules error, miss rule \"%s\"\n", pSymbol->Name);
						exit(1);
					}
				}
				
				pSymbolPtr2 = &(*pSymbolPtr2)->pNextSymbol;
			}
			
			pSymbolPtr1 = &(*pSymbolPtr1)->pOther;
		}

		pRule = pRule->pNextRule;
	}

	return pHead;
}

/*
功能：
	创建一个新的 Rule。

参数：
	pRuleName -- 文法的名字。
	
返回值：
	Rule 指针	
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
	创建一个新的 Symbol。
	
返回值：
	RuleSymbol 指针	
*/
RuleSymbol* CreateSymbol()
{
	RuleSymbol* pSymbol = (RuleSymbol*)malloc(sizeof(RuleSymbol));

	pSymbol->pNextSymbol = NULL;
	pSymbol->pOther = NULL;
	pSymbol->isToken = -1;
	pSymbol->TokenName[0] = '\0';
	pSymbol->pRule = NULL;

	return pSymbol;
}

/*
功能：
	根据 RuleName 在文法链表中查找名字相同的文法。

参数：
	pHead -- 文法链表的头指针。
	RuleName -- 文法的名字。
	
返回值：
	如果存在名字相同的文法返回 Rule 指针，否则返回 NULL	
*/
Rule* FindRule(Rule* pHead, const char* RuleName)
{
	Rule* pRule;
	for(pRule = pHead; pRule != NULL; pRule = pRule->pNextRule)
	{
		if(0 == strcmp(pRule->RuleName, RuleName))
		{
			break;
		}
	}
	
	return pRule;
}	

/*
功能：
	输出文法。

参数：
	pHead -- 文法链表的头指针。
*/
void PrintRule(Rule* pHead)
{
	
	const Rule* pRule;
	for(pRule = pHead;pRule != NULL;pRule = pRule->pNextRule)
	{
		printf("%s -> ",pRule->RuleName);
		RuleSymbol* pSelect = pRule->pFirstSymbol;
		for(;pSelect != NULL;pSelect = pSelect->pOther)
		{
			RuleSymbol* pRuleSymbol = pSelect;
			for(;pRuleSymbol != NULL;pRuleSymbol = pRuleSymbol->pNextSymbol)
			{
				if(pRuleSymbol->isToken == 1)
				{
					printf("%s ",pRuleSymbol->TokenName);
				}
				else
				{
					printf("%s ",pRuleSymbol->pRule->RuleName);
				}
			
			}
			if(pSelect->pOther != NULL)
			{
				printf("| ");
			}
	  	}
	  printf("\n");
	}
}