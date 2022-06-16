#include "shuntingyard.h"

Shunting_yard::Shunting_yard()
{
   _postfix = NULL;
   //Set postfix Queue to NULL
}

Shunting_yard::Shunting_yard(Vector<SToken*> infix)
{
    _postfix = _get_post_fix(infix);
    //gets the postfix form _get_post_fix func
}



Vector<SToken*> Shunting_yard::postfix()
{
    return _postfix;
}


Vector<SToken*> Shunting_yard::_get_post_fix(Vector<SToken*> infix)
{
    bool debug = false;
    //1.declare a postfix Queue
    Vector<SToken*> post;

    //2.declare a stack
    Stack<SToken*> s;

    //3.go through infix Queue
   for(int i=0; i<infix.get_size(); i++)
    {
        //if type of item is one of below, directly push them into
        //postfix Queue
        if(infix[i]->typeOf() == SYM)
        {
            post.push_back(infix[i]);
        }

        //if type of item is Left Paren then put it in Stack
        else if(infix[i]->typeOf() == LPAREN)
        {
            s.push(infix[i]);
        }

        //if type of item is operator
        else if(infix[i]->typeOf() == COPERATOR)
        {

            s.push(infix[i]);

        }

        //if type of item is operator
        else if(infix[i]->typeOf() == LOPERATOR)
        {

            //1.check to see if Stack is empty
            if(s.begin() == NULL)
            {
                s.push(infix[i]);
            }

            else
            {
                //find top of the Stack
                SToken* p = s.top();

                //item from infix Queue that goes into Stack
                //we change out Token* to Operator* and call prec func
                int next = static_cast<LOperator*>(infix[i])->prec();
                if(debug)
                {
                    cout << "NOW: ";
                     infix[i]->print();
                }

                if(debug) cout << "Prec: " << next << endl;
                int prev  = 0;

                //if top of stack is Operator
                if(p->typeOf() == LOPERATOR)
                {
                    //same as next we change type of pointer to Op
                    prev = static_cast<LOperator*>(p)->prec();
                    if(debug)
                    {
                        cout << "Prev: ";
                        p->print();

                        cout << "Prec: " << prev << endl;
                    }
                }
                else if(p->typeOf() == COPERATOR)
                {
                    //same as next we change type of pointer to Op
                    prev = static_cast<COperator*>(p)->prec();
                    if(debug)
                    {
                        cout << "Prev: ";
                        p->print();

                        cout << "Prec: " << prev << endl;
                    }

                }

                //2.check to see if item from infix Queue that goes
                //into Stack has higher prec than top of Stack
                if(next > prev)
                {

                   s.push(infix[i]);
                }
                else
                {
//                    //if not then we pop Stack and put the popped item
//                    //in postfix Queue
//                    post.push_back(s.pop());
//                   //then push item from infix Queue in Stack
//                    s.push(infix[i]);
                    while(!s.empty() && next < prev)
                    {
                        post.push_back(s.pop());
                        if(!s.empty())
                        {

                            p = s.top();
                            if(p->typeOf() == LOPERATOR)
                            {
                                //same as next we change type of pointer to Op
                                prev = static_cast<LOperator*>(p)->prec();
                                if(debug)
                                {
                                    cout << "Prev: ";
                                    p->print();

                                    cout << "Prec: " << prev << endl;
                                }
                            }
                            else if(p->typeOf() == COPERATOR)
                            {
                                //same as next we change type of pointer to Op
                                prev = static_cast<COperator*>(p)->prec();
                                if(debug)
                                {
                                    cout << "Prev: ";
                                    p->print();

                                    cout << "Prec: " << prev << endl;
                                }

                            }

                            else if(p->typeOf() == LPAREN)
                            {
                                //same as next we change type of pointer to Op
                                prev = static_cast<LParen*>(p)->prec();
                                if(debug)
                                {
                                    cout << "Prev: ";
                                    p->print();

                                    cout << "Prec: " << prev << endl;
                                }

                            }
                        }

                    }

                    s.push(infix[i]);

                }
            }


        }

        //if Type was something else(Right Paren)
        else
        {
            //locate top of the stack
            SToken* p = s.top();

            //while haven't reached Left Paren
            while(p->typeOf() != LPAREN)
            {
                if(p->typeOf() != LPAREN)
                {
                    //pop items from Stack into postfix Queue
                    post.push_back(s.pop());
                }
                else
                {
                    s.pop();
                }

                //each time set p pointer to top of Stack
                p = s.top();
            }
            //pop last L paren
            s.pop();
        }
 }

    //at the end put all the remainings from Stack into postfix Queue
    if(s.begin() != NULL)
    {
        while(!s.empty())
        {
            post.push_back(s.pop());
        }
    }

    return post;

}
