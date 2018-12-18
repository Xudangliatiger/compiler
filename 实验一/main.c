#include "RegexpToNFA.h"
#include "RegexpToPost.h"
#include "NFAFragmentStack.h"

NFAFragmentStack FragmentStack;	// ջ�����ڴ��� NFA Ƭ��


 //  char* regexp = "ab";		// �� 1
  // char* regexp = "a|b";	// �� 2
  // char* regexp = "a*";		// �� 3
 // char* regexp = "a?";		// �� 4
 //char* regexp = "a+";		// �� 5
// char* regexp = "a(a|1)*";// �� 6
// char* regexp = "(aa|b)*a(a|bb)*";// �� 7
 char* regexp = "(a|b)*a(a|b)?"; 	// �� 8

int main(int argc, char **argv)
{
	char *post;
	NFAState *start;
	
	//
	// ��ʼ��ջ
	//
	InitNFAFragmentStack(&FragmentStack);
	
	//
	// ���� re2post ������������ʽ�ַ���ת���ɽ������ĺ�����������
	//
	post = re2post(regexp);
	
	//
	// ���� post2nfa �������������ĺ�����������ת��Ϊ NFA �����ؿ�ʼ״̬
	//
	start = post2nfa(post);
				
	return 0;
}

/*
���ܣ�
	��ʼ��һ��״̬��
	  
����ֵ��
	״ָ̬�롣
*/
int nstate = 1;  // ״̬��������
NFAState* CreateNFAState()
{
	NFAState *s = (NFAState*)malloc(sizeof(NFAState));

	s->Name = nstate++;
	s->Transform = '\0';
	s->Next1 = NULL;
	s->Next2 = NULL;
	s->AcceptFlag = 0;
	
	return s;
}

/*
���ܣ�
	����ʼ״̬�ͽ���״̬���һ�� Fragment��
	
������
	StartState -- ��ʼ״̬��
	AcceptState -- ����״̬��	
	  
����ֵ��
	 Fragment �ṹ��ָ�롣
*/
NFAFragment MakeNFAFragment(NFAState *StartState, NFAState *AcceptState)
{
	NFAFragment n = {StartState, AcceptState};
	return n;
}

/*
���ܣ�
	���������ĺ�������ת��Ϊ NFA��

������
	postfix -- �������ĺ�������ָ�롣
	  
����ֵ��
	NFA �Ŀ�ʼ״ָ̬�롣
*/
const char VoidTrans = '$'; // ��ʾ��ת��
NFAState* post2nfa(char *postfix)
{
	char *p;							   		// �α�
	NFAFragment fragment1, fragment2, fm;     	// NFA Ƭ�νṹ�����
	NFAFragment fragment = {0, 0};			   	// ��ʼ�����ڷ��ص� NFA Ƭ��
	NFAState *NewStartState, *NewAcceptState; 	// ��ʼ״̬�ͽ���״ָ̬��
	
		for(p=postfix; *p != '\0'; p++)
	{
		switch(*p)
		{
			default:	// ���쵥�ַ� NFA Ƭ��
				// ���� CreateNFAState �������������µ�״̬
				NewStartState = CreateNFAState();
				NewAcceptState = CreateNFAState();
				// ��ʼ״̬ͨ�����ַ�ת��������״̬
				NewStartState->Transform = *p;
				NewStartState->Next1 = NewAcceptState;
				NewAcceptState->AcceptFlag = 1;
				// ���� MakeNFAFragment ��������һ���µ� NFA Ƭ��, ����ջ
				fm = MakeNFAFragment(NewStartState, NewAcceptState);
				PushNFAFragment(&FragmentStack, fm);
				break;
			case '.':	// �������� NFA Ƭ��
				// ջ��������Ƭ�γ�ջ�������µ� NFA Ƭ��
				fragment2 = PopNFAFragment(&FragmentStack);
				fragment1 = PopNFAFragment(&FragmentStack);
				// Ƭ�� 1 ͨ����ת����Ƭ�� 2 ����
				fragment1.AcceptState->AcceptFlag = 0;
				fragment1.AcceptState->Next1 = fragment2.StartState;
				fragment1.AcceptState->Transform = VoidTrans;
				// ���� MakeNFAFragment ��������һ���µ� NFA Ƭ��, ����ջ
				fm = MakeNFAFragment(fragment1.StartState, fragment2.AcceptState);
				PushNFAFragment(&FragmentStack, fm);
				break;
			case '|':	// ����ѡ�� NFA Ƭ�� 
				NewStartState = CreateNFAState();
				NewAcceptState = CreateNFAState();
				//��ջ��������Ƭ�γ�ջ�������µ� NFA Ƭ��, ����ջ
				fragment2 = PopNFAFragment(&FragmentStack);
				fragment1 = PopNFAFragment(&FragmentStack);
				// 
				NewStartState->Transform = VoidTrans;
				NewStartState->Next1 = fragment1.StartState;
				NewStartState->Next2 = fragment2.StartState;
				//NewStartState->AcceptFlag = 0;
			
				//
				NewAcceptState->AcceptFlag = 1;
				//NewAcceptState->Next1 = NULL;
				//NewAcceptState->Next2 = NULL;
				//NewAcceptState->Transform = VoidTrans;
				//
				fragment1.AcceptState->AcceptFlag = 0;
				fragment1.AcceptState->Next1 = NewAcceptState;
				fragment1.AcceptState->Transform = VoidTrans;
				
				
				fragment2.AcceptState->AcceptFlag = 0;
				fragment2.AcceptState->Next1 = NewAcceptState;
				fragment2.AcceptState->Transform = VoidTrans;
				//
				// ���� MakeNFAFragment ��������һ���µ� NFA Ƭ��, ����ջ
				fm = MakeNFAFragment(NewStartState, NewAcceptState);
				PushNFAFragment(&FragmentStack, fm);
				break;
				
			case '*':	// �����Ǻ� NFA Ƭ��

				fragment1 = PopNFAFragment(&FragmentStack);
				
				
				// 
				NewStartState = CreateNFAState();
				NewAcceptState = CreateNFAState();
				//
				NewStartState->AcceptFlag = 0;
				NewStartState->Transform = VoidTrans;
				NewStartState->Next1 = fragment1.StartState;
				NewStartState->Next2 = NewAcceptState;
				
				fragment1.AcceptState->Next1 = NewAcceptState;
				fragment1.AcceptState->Next2 = fragment1.StartState;
				fragment1.AcceptState->Transform = VoidTrans;
				fragment1.AcceptState->AcceptFlag = 0;
				
				NewAcceptState->AcceptFlag = 1;
				
				
				//
				
				 
				fm = MakeNFAFragment(NewStartState, NewAcceptState);
				PushNFAFragment(&FragmentStack, fm);
				break;
				
				
				
			case '?':	// �����ʺ� NFA Ƭ��
			//	��ջ����һ��Ƭ�γ�ջ�������µ� NFA Ƭ��, ����ջ
				fragment1 = PopNFAFragment(&FragmentStack);
			
			
				// 
				NewStartState = CreateNFAState();
				NewAcceptState = CreateNFAState();
				//
				NewStartState->AcceptFlag = 0;
				NewStartState->Transform = VoidTrans;
				NewStartState->Next2 = NewAcceptState;
				NewStartState->Next1 = fragment1.StartState;
				NewAcceptState->AcceptFlag = 1;
				NewAcceptState->Transform = VoidTrans;
				//
				fragment1.AcceptState->AcceptFlag = 0;
				fragment1.AcceptState->Next1 = NewAcceptState;
				fragment1.AcceptState->Transform = VoidTrans;
				//
				// ���� MakeNFAFragment ��������һ���µ� NFA Ƭ��, ����ջ
				fm = MakeNFAFragment(NewStartState, NewAcceptState);
				PushNFAFragment(&FragmentStack, fm);
				break;
		
			case '+':	// ����Ӻ� NFA Ƭ��
				//	��ջ����һ��Ƭ�γ�ջ�������µ� NFA Ƭ��, ����ջ
				fragment1 = PopNFAFragment(&FragmentStack);
				// 
				
				NewAcceptState = CreateNFAState();
				//  
			
				//
				NewAcceptState->AcceptFlag = 1;
				NewAcceptState->Transform = VoidTrans;
				NewAcceptState->Next1 = fragment1.StartState ;
				//
				fragment1.AcceptState->AcceptFlag = 0;
				fragment1.AcceptState->Next1 = NewAcceptState;
				fragment1.AcceptState->Transform = VoidTrans;	
				
				// ���� MakeNFAFragment ��������һ���µ� NFA Ƭ��, ����ջ
				fm = MakeNFAFragment(fragment1.StartState, NewAcceptState);
				PushNFAFragment(&FragmentStack, fm);
				break;
		}
	}
	
	//�� NFA ���ս����ջ���浽 fragment ��
	fragment.StartState = PopNFAFragment(&FragmentStack).StartState;
	
	return fragment.StartState;
}

