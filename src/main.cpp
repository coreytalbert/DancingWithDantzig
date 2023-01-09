#include "matrix.h"
#include "MatrixElement.h"
#include "MatrixRow.h"
/*Gaussian elimination to produce reduced row echelon form */
/*Elementary row operations*/
/* xRa      -> Ra */
/* xRa + Rb -> Rb */
/*  Ra + Rb -> Rb */

/* matrix multiplication */
/* scalar multiplication **/
/* determinant ? */
// square



int main( /*int argc , char * argv[]*/ )
{

    Matrix<float> mat( 3 ) ;
    mat.display();
    mat.transpose();
    puts( "" );
    mat.display();

    mat.scale( 0.5 );
    puts( "" );
    mat.display();

    mat.transpose();
    puts( "" );
    mat.display();

    Matrix<float> rec( 2 , 3 );
    puts( "" );
    rec.display();

    rec.transpose();
    puts( "" );
    rec.display();

    return 0 ;
}