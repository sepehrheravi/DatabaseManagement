#include "rpn.h"

RPN::RPN(Vector<SToken*> post_fix_vec) : postfix(post_fix_vec)
{

}


vector<long> RPN::get_record(Map<string, int>& fields,
                             vector<MMap<string, long>>& indices)
{
    bool debug = false;
    Vector<SToken*> post_fix_vec = postfix;
    Stack<SToken*> final_stack;

    for (int i=0; i<post_fix_vec.get_size(); i++)
    {
        SToken* current = post_fix_vec[i];

        if (current->typeOf() == SYM)
        {
            if(debug)
            {
                cout << "SYM: ";
                current->print();
                cout << endl;
            }
            final_stack.push(current);

        }
        else if (current->typeOf() == COPERATOR)
        {
            if(debug)
            {
                cout << "OPER: ";
            }

            //vec for recno
            vector<long> vec;

            //change from SToken* to Coperator so we can use ->oper()
            string op = static_cast<COperator*>(current)->oper();


            //first one would be cond and econd field
            Symbol* cond = static_cast<Symbol*>(final_stack.pop());
            Symbol* field = static_cast<Symbol*>(final_stack.pop());


            if(debug)
            {
                cout << op << endl;

                cout << "cond: ";
                cond->print();
                cout << endl;

                cout << "field: ";
                field->print();
                cout << endl;
            }


            if (op == "=")
            {
                //if operator = just simply check to see if in that MMap the
                //condition exists
                if (indices[fields[field->str()]].contains(cond->str()))
                {
                    vec = indices[fields[field->str()]][cond->str()];
                }
            }


            //for rest we have to call upper and lower bounds since it's not
            //just one value like =
            else if (op == "<")
            {
                if(debug)
                {
                    cout << "< called" << endl;
                    MMap<string, long>:: Iterator it = indices[fields[field->str()]].begin();
                    cout << (*it) << endl;
                    MMap<string, long>:: Iterator it1 = indices[fields[field->str()]].lower_bound(cond->str());
                    cout << (*it1) << endl;
                }


                for(MMap<string, long>:: Iterator it = indices[fields[field->str()]].begin();
                    it != indices[fields[field->str()]].lower_bound(cond->str()); it++)
                {
                    if(debug) cout << (*it) << endl;
                    vector<long> value = (*it).value_list;

                    //we don't want to have a recno twice so jsut union them
                    vec = Union(vec, value);

                }
            }

            else if (op == "<=")
            {
                if(debug)
                {
                    cout << "< called" << endl;
                    MMap<string, long>:: Iterator it = indices[fields[field->str()]].begin();
                    cout << (*it) << endl;
                    MMap<string, long>:: Iterator it1 = indices[fields[field->str()]].lower_bound(cond->str());
                    cout << (*it1) << endl;
                }



                for(MMap<string, long>:: Iterator it = indices[fields[field->str()]].begin();
                    it != indices[fields[field->str()]].upper_bound(cond->str()); it++)
                {
                    if(debug) cout << (*it) << endl;
                    vector<long> value = (*it).value_list;
                    vec = Union(vec, value);

                }
            }

            else if (op == ">")
            {
                if(debug)
                {
                    cout << "< called" << endl;
                    MMap<string, long>:: Iterator it = indices[fields[field->str()]].begin();
                    cout << (*it) << endl;
                    MMap<string, long>:: Iterator it1 = indices[fields[field->str()]].lower_bound(cond->str());
                    cout << (*it1) << endl;
                }



                for(MMap<string, long>:: Iterator it = indices[fields[field->str()]].upper_bound(cond->str());
                    it != indices[fields[field->str()]].end(); it++)
                {
                    if(debug) cout << (*it) << endl;
                    vector<long> value = (*it).value_list;
                    vec = Union(vec, value);

                }
            }

            else if (op == ">=")
            {
                if(debug)
                {
                    cout << "< called" << endl;
                    MMap<string, long>:: Iterator it = indices[fields[field->str()]].begin();
                    cout << (*it) << endl;
                    MMap<string, long>:: Iterator it1 = indices[fields[field->str()]].lower_bound(cond->str());
                    cout << (*it1) << endl;
                }



                for(MMap<string, long>:: Iterator it = indices[fields[field->str()]].lower_bound(cond->str());
                    it != indices[fields[field->str()]].end(); it++)
                {
                    if(debug) cout << (*it) << endl;
                    vector<long> value = (*it).value_list;
                    vec = Union(vec, value);

                }
            }

            //push vec that we got of recno back into stack

            final_stack.push(new Recno(vec));
        }

        //if type of Oper is LOperator ( and or)
        else if (current->typeOf() == LOPERATOR)
        {
            //get the current operator
            string op = static_cast<LOperator*>(current)->oper();

            //pop stack for first and second SToken* of tpye Recno*
            Recno* first = static_cast<Recno*>(final_stack.pop());
            Recno* second = static_cast<Recno*>(final_stack.pop());


            vector<long> v1 = first->rec_vec();
            vector<long> v2 = second->rec_vec();

            if (op == "and")
            {
                //for and we use intersection
                final_stack.push(new Recno(Intersection(v1, v2)));
            }
            else if (op == "or")
            {
                //for or just union
                final_stack.push(new Recno(Union(v1, v2)));
            }

        }
    }

    //last step is to push the last item in the stack


    vector<long> final = static_cast<Recno*>(final_stack.pop())->rec_vec();

    if(!final_stack.empty())
        cout << "SOMETHING IS WRONG, STACK IS NOT EMPTY" << endl;

    return final;

}
