#include "Follow.h"

const char* VoidSymbol = "#"; // "��"
const char* DollarSymbol = "$";

int main(int argc, char* argv[])
{
	//
	// ���� InitRules ������ʼ���ķ�
	//
	Rule* pHead = InitRules();

	//
	// ��ʼ�� First ���ϡ�Follow ����
	//
	SetList FirstSetList, FollowSetList;
	FirstSetList.nSetCount = 0;
	FollowSetList.nSetCount = 0;

	//
	// ���� Follow �������ķ��� First ���ϡ�Follow ����
	//
	Follow(pHead, &FollowSetList, &FirstSetList);

	//
	// ����ķ�
	//
	PrintRule(pHead);
	
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

	//
	// TODO: �ڴ���Ӵ���
	//
	
}

/*
���ܣ�
	���������� SetList �в��ҡ�

������
	pSetList -- SetList ָ�롣
	pName -- ���������ַ���ָ�롣
	  
����ֵ��
	����ҵ����� Set ָ�룬���򷵻� NULL��
*/
Set* GetSet(SetList* pSetList, const char* pName)
{

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
	��ӳɹ����� 1�����򷵻� 0��
*/
int AddTerminalToSet(Set* pSet, const char* pTerminal)
{

	//
	// TODO: �ڴ���Ӵ���
	//
	
}

/*
���ܣ�
	��Դ Set ��ӵ�Ŀ�� Set �У����Ԧš�

������
	pDesSet -- Ŀ�� Set ָ�롣
	pSrcSet -- Դ Set ָ�롣
	  
����ֵ��
	��ӳɹ����� 1�����򷵻� 0��
*/
int AddSetToSet(Set* pDesSet, const Set* pSrcSet)
{

	//
	// TODO: �ڴ���Ӵ���
	//
	
}

/*
���ܣ�
	�ж� Set ���Ƿ��Цš�

������
	pSet -- Set ָ�롣
	  
����ֵ��
	���ڷ��� 1��
	�����ڷ��� 0��
*/
int SetHasVoid(const Set* pSet)
{

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
	
}

/*
���ܣ�
	���ķ��� Follow ���ϡ�

������
	pHead -- �ķ���ͷָ�롣
	pFollowSetList -- Follow ����ָ�롣
	pFirstSetList -- First ����ָ�롣
*/
void Follow(const Rule* pHead, SetList* pFollowSetList, SetList* pFirstSetList)
{
	const Rule* pRule;	// Rule ָ��
	int isChange;		// �����Ƿ��޸ĵı�־
	RuleSymbol* pSymbol;// Symbol �α�

	// ���� First �������ķ��� First ����
	First(pFirstSetList, pHead);

	// ʹ���ķ������ʼ�� Follow ����
	for(pRule = pHead; pRule != NULL; pRule = pRule->pNextRule)
	{
		AddOneSet(pFollowSetList, pRule->RuleName);
	}

	// �ڿ�ʼ���ŵ� Follow �����м����ս�� $
	AddTerminalToSet(&pFollowSetList->Sets[0], DollarSymbol);

	do
	{
		isChange = 0; // ���ü����޸ı�־

		for(pRule = pHead; pRule != NULL; pRule = pRule->pNextRule)
		{
			for(pSymbol = pRule->pFirstSymbol; pSymbol != NULL; pSymbol = pSymbol->pNextSymbol)
			{
				// �����ս��
				if(pSymbol->isToken)
					continue;

				// ��ʼ��һ�� First ���� TempFirstSet����Ϊ��ʱ����
				Set TempFirstSet;
				TempFirstSet.nTerminalCount = 0;

				if(NULL != pSymbol->pNextSymbol)
				{
					if(pSymbol->pNextSymbol->isToken) // �ս��
					{
						// ���� AddTerminalToSet ���������ս�����뵽 TempFirstSet
						AddTerminalToSet(&TempFirstSet, pSymbol->pNextSymbol->SymbolName);
					}
					else // ���ս��
					{
						// ���� GetSet ������ pFirstSetList �в��� Set
						Set* pFirstSetXn = GetSet(pFirstSetList, pSymbol->pNextSymbol->SymbolName);

						// ���ҵ��� Set ���� TempFirstSet ��
						AddSetToSet(&TempFirstSet, pFirstSetXn);
					}
				}
				else
				{
					// ���� AddTerminalToSet ������ VoidSymbol ���뵽 TempFirstSet ��
					AddTerminalToSet(&TempFirstSet, VoidSymbol);
				}

				// ���� GetSet ������ pFollowSetList �в��� Set
				Set* pFollowSetXi = GetSet(pFollowSetList, pSymbol->SymbolName);

				// ������ TempFirstSet ���� pFollowSetXi
				if(AddSetToSet(pFollowSetXi, &TempFirstSet))
					isChange = 1; // ���ü����޸ı�־

				if(SetHasVoid(&TempFirstSet)) // �жϼ��� TempFirstSet �Ƿ��Ц�
				{
					// ���� GetSet �����õ���ǰ�ķ����ƶ�Ӧ�� Follow ����
					Set* pFollowSetA = GetSet(pFollowSetList, pRule->RuleName);

					// ������ pFollowSetA ���� pFollowSetXi
					if(AddSetToSet(pFollowSetXi, pFollowSetA))
						isChange = 1; // ���ü����޸ı�־
				}
			}
		}

	} while(isChange);
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

