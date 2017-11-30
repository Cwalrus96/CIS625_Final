#include "individual.h"
#include "constants.h"
#include "cga.h"

int main()
{
   //GAGAGA GAGAG AGAGAGAG
   double model[] = {30611,113.064,0.5289,0.5916,0.0426,1.3484,80.5297,2.85,2.25,2.9699,1017.1};
   CGA cga(model, 0.1);
   const double res = cga.run();

   return 0;
}
