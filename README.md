# triangulations_surfaces

Program "Thurston.py" illustrates Figure 4 from "Shapes of polyhedra and triangulations of the sphere', William P Thurston
Counted number  f(m) of quadruples (n, p1, p2, p3) -- solutions  for a system
m = n^2 - p1^2 - p2^2 - p3^2, p1, p2, p3 >=0, p1 + p2 <= n, p2 + p3 <= n, p1 + p3 <=  n

Data averaged over window size 50
One can see that graph resembling linear function f(m) = km
Coefficient k here -- 1/8 volume of Whitehead link

Program "projective_plane.c" does the same thing for RP^2 with 3 conic points of equal defect (2pi/3).
Formula for square is S = |z|^2(ab + ac + ad + bc + bd + cd). Where a, b, c, d -- whole numbers, z - "prime"  vector on Eisenstein lattice.
