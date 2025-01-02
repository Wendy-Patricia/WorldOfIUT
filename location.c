#include "location.h"
#include <string.h> /* strdup */
#include <stdio.h>  /* printf */
#include <stdlib.h> /* malloc, free */

extern Location *LocationNew(char *name, char *desc)
{
   Location *ret = (Location *)NULL;
   if (name && desc) /** && where)**/
   {
      ret = malloc(sizeof(Location));
      if (ret)
      {
         ret->name = strdup(name);
         ret->desc = strdup(desc);
      }
      // ret->currentLocation = NULL;
   }
   return ret;
}

extern void LocationDelete(Location *l)
{
   if (l)
   {
      if (l->name)
         free(l->name);
      if (l->desc)
         free(l->desc);
      free(l);
   }
   return (Location *)NULL;
}

extern void LocationPrint(Location *l)
{
   if (l)
      printf("%s\n%s\n", l->name, l->desc);
}