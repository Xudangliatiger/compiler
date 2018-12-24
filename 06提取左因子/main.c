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
	int i = 0;
	int j = 0;
	int k = 0;
	int temp = 0;
	RuleSymbol* pScan = NULL;
	RuleSymbol* pScan1 = NULL;
	RuleSymbol* pScan2 = NULL;
	
	for(pScan = pSelectTemplate; pScan != NULL; pScan = pScan->pNextSymbol, j++)
	{
		pScan1 = pSelectTemplate->pOther;
		if(pScan1 == NULL)
		break;
		for(pScan1 = pSelectTemplate->pOther; pScan1 != NULL; pScan1 = pScan1->pOther)
		{
			temp++;
			pScan2 = pScan1;
			for(k = 0;k < j; k++)
			{
				pScan2 = pScan2->pNextSymbol;
				if(pScan2 == NULL)
				break;
			}
			if(!SymbolCmp(pScan, pScan2))
			break;
		}
		if(temp != 0)
		{
			if(pScan1 == NULL)
			{
				i++;
			}
			else
			return i;
			temp = 0;
		}
	}
	return i;
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
	if(pSymbol1 == NULL || pSymbol2 == NULL)
	return 0;
	if(pSymbol1->isToken == 1 && pSymbol2->isToken == 1)
	{
		if(!strcmp(pSymbol1->TokenName, pSymbol2->TokenName))
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
	else if(pSymbol1->isToken == 0 && pSymbol2->isToken == 0)
	{
		if(!strcmp(pSymbol1->pRule->RuleName, pSymbol2->pRule->RuleName))
		{
			return 1;
		}
		else
		{
			return 0;
		}	
	}
	else
	return 0;
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
	RuleSymbol* pSymbolCursor1;
	RuleSymbol* pSymbolCursor2;
	int i = 0;
	
	pSymbolCursor1 = pSelectTemplate;
	pSymbolCursor2 = pSelect;
	for(i = 0; i < Count; i++)
	{
		if(SymbolCmp(pSelectTemplate, pSelect))
		{
			pSymbolCursor1 = pSymbolCursor1->pNextSymbol;
			if(pSymbolCursor2->pNextSymbol != NULL)
			pSymbolCursor2 = pSymbolCursor2->pNextSymbol;
			else
			pSymbolCursor2 = NULL;
			continue;
		}
		else
		break;
	}
	
	if(i == Count)
	return 1;
	else
	return 0;
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
	RuleSymbol* pSelectTemp;
	pSelectTemp = pRule->pFirstSymbol;
	//�ķ���ǰ���κι���ʱ
	if(pSelectTemp == NULL){
		//�� Select Ϊ NULL ʱ�ͽ�һ�����ս�����뵽�ķ�ĩβ
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
		//selectָ���Ƶ���ǰ�ķ����һ��select
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
	Rule* pRule;		    	 // Rule �α�
	int isChange;				 // Rule �Ƿ���ȡ�����ӵı�־
	RuleSymbol* pSelectTemplate; // Select �α�
	Rule* pNewRule; 			 // Rule ָ��
	RuleSymbol* pSelect;		 // Select �α�
	 
	
	do
	{
		int i = 0;
		RuleSymbol* pSymbolCursor = NULL;
		RuleSymbol* pSymbolCursor1 = (RuleSymbol*)malloc(sizeof(RuleSymbol));
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
			if(Count == 0 )
				continue;

			pNewRule = CreateRule(pRule->RuleName); // ������ Rule
			GetUniqueRuleName(pRule, pNewRule->RuleName);
			isChange = 1; // ���ñ�־

			//���� AddSelectToRule ������ģ��������֮��Ĳ��ּӵ��� Rule ��ĩβ
			pSymbolCursor = pSelectTemplate;
			for(i = 0; i < Count-1; i++)
			{
				pSymbolCursor = pSymbolCursor->pNextSymbol;
			}
			AddSelectToRule(pNewRule, pSymbolCursor->pNextSymbol);
			//��ģ��������֮��Ĳ����滻Ϊָ���� Rule �ķ��ս��
			pSymbolCursor1 = CreateSymbol();
			pSymbolCursor1->pOther = NULL; 
			pSymbolCursor1->isToken = 0;
			pSymbolCursor1->pRule = pNewRule;
			pSymbolCursor->pNextSymbol = pSymbolCursor1;
			// ��ģ��֮���λ��ѭ�����Ұ��������ӵ� Select������ȡ������
			pSelect = pSelectTemplate->pOther;
			RuleSymbol **pSelectPtr = &pSelectTemplate;
			while(pSelect != NULL)
			{
				if(NeedPickup(pSelectTemplate, Count, pSelect)) // Select ����������
				{
					//���� AddSelectToRule ������������֮��Ĳ��ּӵ��� Rule ��ĩβ
					pSymbolCursor = pSelect;
					for(i = 0; i < Count; i++)
					{
						pSymbolCursor = pSymbolCursor->pNextSymbol;
					}
					
					AddSelectToRule(pNewRule, pSymbolCursor);
					//���� Select �� Rule ���Ƴ����ͷ��ڴ棬���ƶ��α�
					pSymbolCursor = pSelect;
					pSelect = pSelect->pOther;
					(*pSelectPtr)->pOther = pSelect;
					 FreeSelect(pSymbolCursor);
				}
				else // Select ������������
				{
					//�ƶ��α�
					*pSelectPtr = (*pSelectPtr)->pOther;
				}
			}

			//���� Rule ���뵽�ķ�����
			pRule->pNextRule = pNewRule;
		}

	} while (isChange == 1);
	//
	// TODO: �ڴ���Ӵ���
	//

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

