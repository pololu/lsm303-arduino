#ifndef vector_h
#define vector_h
typedef struct vector
{
  float x, y, z;
} vector;

extern void vector_cross(const vector *a, const vector *b, vector *out);
extern float vector_dot(const vector *a,const vector *b);
extern void vector_normalize(vector *a);
#endif