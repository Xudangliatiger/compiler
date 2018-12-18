#include "PickupLeftFactor.h"

const char* VoidSymbol = "$"; // "��"
const char* Postfix = "'";


int main(int argc, char* argv[])
{
	//
	// ���� InitRules ������ʼ���ķ�
	//
	Rule* pHead = InitRules();

	//
	// �����ȡ������֮ǰ���ķ�
	//
	printf("Before Pickup Left Factor:\n");
	PrintRule(pHead);

	//
	// ���� PickupLeftFactor �������ķ���ȡ������
	//
	PickupLeftFactor(pHead);
	
	//
	// �����ȡ������֮����ķ�
	//
	printf("\nAfter Pickup Left Factor:\n");
	PrintRule(pHead);
	
	return 0;
}

/*
���ܣ�
	�����±��ҵ� Select �е�һ�� Symbol��

������
	pSelect -- Select ָ�롣
	index -- �±ꡣ
	  
����ֵ��
	������ڣ������ҵ��� Symbol ָ�룬���򷵻� NULL��
*/
RuleSymbol* GetSymbol(RuleSymbol* pSelect, int index)
{
	int i = 0;
	RuleSymbol* pRuleSymbol;
	for(pRuleSymbol = pSelect, i = 0; pRuleSymbol != NULL; pRuleSymbol = pRuleSymbol->pNextSymbol, i++)
	{
		if(i == index)
			return pRuleSymbol;
	}

	return NULL;	
}

/*
���ܣ�
	�� SelectTemplate Ϊģ�壬ȷ�������ӵ���󳤶ȡ�

������
	pSelectTemplate -- ��Ϊģ��� Select ָ�롣
	  
����ֵ��
	�����ӵ���󳤶ȣ�������� 0 ˵�������������ӡ�
*/
int LeftFactorMaxLength(RuleSymbol* pSelectTemplate)
{

	//
	// TODO: �ڴ���Ӵ���
	//
	
}

/*
���ܣ�
	�Ƚ�������ͬ����(ͬΪ�ս����ͬΪ���ս��)�� Symbol �Ƿ������ͬ�����֡�

������
	pSymbol1 -- Symbol ָ�롣
	pSymbol2 -- Symbol ָ�롣
	  
����ֵ��
	��ͬ���� 1����ͬ���� 0��
*/
int SymbolCmp(RuleSymbol* pSymbol1, RuleSymbol* pSymbol2)
{

	//
	// TODO: �ڴ���Ӵ���
	//
	
}

/*
���ܣ�
	ȡ�ķ��е�һ�� Select �� SelectTemplate ���бȽϣ��жϸ� Select �Ƿ���Ҫ��ȡ�����ӡ�

������
	pSelectTemplate -- ��Ϊģ��� Select ָ�롣
	Count -- SelectTemplate ����ȷ���������ӵ�������
	pSelect -- Select ָ�롣
	  
����ֵ��
	��� Select ���������ӷ��� 1�����򷵻� 0��
*/
int NeedPickup(RuleSymbol* pSelectTemplate, int Count, RuleSymbol* pSelect)
{

	//
	// TODO: �ڴ���Ӵ���
	//
	
}

/*
���ܣ�
	��һ�� Select ���뵽�ķ�ĩβ���� Select Ϊ NULL ʱ�ͽ�һ�����ս�����뵽�ķ�ĩβ��

������
	pRule -- �ķ�ָ�롣
	pNewSelect -- Select ָ�롣
*/
void AddSelectToRule(Rule* pRule, RuleSymbol* pNewSelect)
{

	//
	// TODO: �ڴ���Ӵ���
	//
	
}

/*
���ܣ�
	�� pRuleName ���ķ��е����� RuleName �Ƚ�, �����ͬ������һ����׺��

������
	pHead -- Rule �����ͷָ�롣
	pRuleName -- Rule �����֡�
*/
void GetUniqueRuleName(Rule* pHead, char* pRuleName)
{
	Rule* pRuleCursor = pHead;
	for(; pRuleCursor != NULL;)
	{
		if(0 == strcmp(pRuleCursor->RuleName, pRuleName))
		{
			strcat(pRuleName, Postfix);
			pRuleCursor = pHead;
			continue;
		}
		pRuleCursor = pRuleCursor->pNextRule;
	}	
}

/*
���ܣ�
	�ͷ�һ�� Select ���ڴ档

������
	pSelect -- ��Ҫ�ͷŵ� Select ��ָ�롣
*/
void FreeSelect(RuleSymbol* pSelect)
{

	//
	// TODO: �ڴ���Ӵ���
	//

}

/*
���ܣ�
	��ȡ�����ӡ�

������
	pHead -- �ķ���ͷָ�롣
*/
void PickupLeftFactor(Rule* pHead)
{
	Rule* pRule;				// Rule ָ��
	int isChange;				// Rule �Ƿ���ȡ�����ӵı�־
	RuleSymbol* pSelectTemplate;// Select �α�
	Rule* pNewRule;				// �� Rule ָ��
	RuleSymbol* pSelect;		// Select �α�

	do
	{
		isChange = 0;

		for(pRule = pHead; pRule != NULL; pRule = pRule->pNextRule)
		{
			// ȡ Rule �е�һ�� Select ��Ϊģ�壬���� LeftFactorMaxLength ����ȷ�������ӵ���󳤶�
			int Count = 0;
			for(pSelectTemplate = pRule->pFirstSymbol; pSelectTemplate != NULL; pSelectTemplate = pSelectTemplate->pOther)
			{
				if((Count = LeftFactorMaxLength(pSelectTemplate)) > 0)
					break;
			}

			// ����û�������ӵ� Rule
			if(Count == 0)
				continue;

			pNewRule = CreateRule(pRule->RuleName); // ������ Rule
			GetUniqueRuleName(pRule, pNewRule->RuleName);
			isChange = 1; // ���ñ�־

			���� AddSelectToRule ������ģ��������֮��Ĳ��ּӵ��� Rule ��ĩβ
			��ģ��������֮��Ĳ����滻Ϊָ���� Rule �ķ��ս��

			// ��ģ��֮���λ��ѭ�����Ұ��������ӵ� Select������ȡ������
			pSelect = pSelectTemplate->pOther;
			RuleSymbol **pSelectPtr = &pSelectTemplate->pOther;
			while(pSelect != NULL)
			{
				if(NeedPickup(pSelectTemplate, Count, pSelect)) // Select ����������
				{
					���� AddSelectToRule ������������֮��Ĳ��ּӵ��� Rule ��ĩβ
					���� Select �� Rule ���Ƴ����ͷ��ڴ棬���ƶ��α�
				}
				else // Select ������������
				{
					�ƶ��α�
				}
			}

			���� Rule ���뵽�ķ�����
		}

	} while (isChange == 1);
}

/*
���ܣ�
	ʹ�ø��������ݳ�ʼ���ķ�����

����ֵ��
	�ķ���ͷָ��
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
	/* A -> abC | abcD | abcE */
	{ "A", {
				{ { 1, "a" }, { 1, "b" }, { 1, "C" } },
				{ { 1, "a" }, { 1, "b" }, { 1, "c" }, { 1, "D" } },
				{ { 1, "a" }, { 1, "b" }, { 1, "c" }, { 1, "E" } }
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
���ܣ�
	����һ���µ� Rule��

������
	pRuleName -- �ķ������֡�
	
����ֵ��
	Rule ָ��	
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
	����һ���µ� Symbol��
	
����ֵ��
	RuleSymbol ָ��	
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
���ܣ�
	���� RuleName ���ķ������в���������ͬ���ķ���

������
	pHead -- �ķ���ͷָ�롣
	RuleName -- �ķ������֡�
	
����ֵ��
	Rule ָ��	
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
���ܣ�
	����ķ���

������
	pHead -- �ķ���ͷָ�롣
*/
void PrintRule(Rule* pHead)
{

	//
	// TODO: �ڴ���Ӵ���
	//
	
}
