- [X] Integral and Derivative for Vector Field
- [X] Function Compound
- [X] standardizate the four function class
  - [X] check points for function definition
  - [X] check points for standard function call inside the class function call
    ```cpp
        void _funcall(A x)
        {
            this->check_funcall_not_empty();
            this->check_argument_size(x);
            auto result=this->_func(x);
            this->check_result_size(result);
            return result;
        }
    ```
- [ ] CalculateErrorReporter
- [ ] code for poly solver
