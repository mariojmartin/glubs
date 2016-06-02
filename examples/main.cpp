
#include <stdio.h>
#include "gparser/gparser.h"

/* Values in the variable is in the .pvalue field, 
* which can point to different data types.
* Check .type and cast to the correct variable 
* The following function just do that. */
static void display_var( const gVariable var )
{
    switch (var.type){
        case t_undefined:{  /* The variable is not set */
            printf( "(null)" );
            break;
        }
        case t_bool:{       /* Boolean type */
            char* p = (char*)var.pvalue;
            if (*p){
                printf( "true" );
            }
            else{
                printf( "false" );
            }
            break;
        }
        case t_byte:{
            _byte_* p = (_byte_*)var.pvalue;
            printf( "(byte)%u", *p );
            break;
        }
        case t_int:{        /* Equivalent to 'int' in C */
            int* p = (int*)var.pvalue;
            printf( "%ii", *p );
            break;
        }
        case t_double:{     /* Equivalent to 'double' in C */
            double* p = (double*)var.pvalue;
            printf( "%.4ed", *p );
            break;
        }
        case t_l64:{        /* integer of 64 bits */
            _l64_* p = (_l64_*)var.pvalue;
            printf( "%lldL", *p );
            break;
        }
        case t_float:{      /* Equivalent to 'float' in C */
            float* p = (float*)var.pvalue;
            printf( "%.4ff", *p );
            break;
        }

        default:
            ; /* Do nothing */
    }
}

/* To simply parser a string only two functions are needed. */
void simple_example()
{
    char command[] = "1+2+3";

    /* First create a parser */
    gParser* parser = gParser_create();

    /* Calculate the aritmetic operations in the string using the parser */
    int status = gParser_command( parser, command );

    /* Check the results */
    if (status == GPARSE_OK){
        /* The solution of the operation is stored in ans */ 
        /* To directly obtain the value as a double */
        double v = gVariable_getasDouble( parser->ans );
        printf( "    %g", v );
    }
    else{ /* (status == GPARSE_ERROR) There is an error */
        printf( "%s", command );

        /* Shows the error message.*/
        printf( "\n%s. ", parser->err_msg );

        /* Indicates the token that has triggered the error. */
        printf( "char: %i ", parser->err_column );
    }

    /* Finally release memory resources */
    gParser_dispose( parser );

    getchar();
}

/* To simply parser a string only two functions are needed. */
int main( int argc, char* argv[] )
{
    printf( "
    simple_example();
}