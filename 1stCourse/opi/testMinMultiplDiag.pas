uses opi_hw;

type matrixx = array of array of integer;

var Matr: matrixx;
    razm : integer;

procedure TestMod(var matrix:matrixx; r:integer; outdiag:string; count:integer);
var mass : string;
begin
mass := MinMultiplDiag(matrix,r);
begin
    if mass <> outdiag then
      writeln('Module MinMultiplDiag test',count,' FAILED')
    else
      writeln('Module MinMultiplDiag test',count,' PASSED');
  end;
end;


procedure test1();
var	i: integer;
    out:string;
begin
razm := 3;
SetLength(Matr,razm);
for i := 0 to 2 do
	SetLength(Matr[i],razm);
Matr[0][0] := 9;
Matr[0][1] := 8;
Matr[0][2] := 7;
Matr[1][0] := 6;
Matr[1][1] := 5;
Matr[1][2] := 4;
Matr[2][0] := 3;
Matr[2][1] := 2;
Matr[2][2] := 1;
out := 'Нет отрицательных элементов';
TestMod(Matr,razm,out,1);
end;

procedure test2();
var	i: integer;
    out:string;
begin
razm := 3;
SetLength(Matr,razm);
for i := 0 to 2 do
	SetLength(Matr[i],razm);
Matr[0][0] := 1;
Matr[0][1] := -2;
Matr[0][2] := 3;
Matr[1][0] := 4;
Matr[1][1] := 5;
Matr[1][2] := -6;
Matr[2][0] := 7;
Matr[2][1] := 8;
Matr[2][2] := 9;
out := ' 8 -6';
TestMod(Matr,razm,out,2);
end;

procedure test3();
var	i: integer;
    out:string;
begin
razm := 4;
SetLength(Matr,razm);
for i := 0 to 3 do
	SetLength(Matr[i],razm);
Matr[0][0] := 1;
Matr[0][1] := 4;
Matr[0][2] := -3;
Matr[0][3] := 4;
Matr[1][0] := 5;
Matr[1][1] := -2;
Matr[1][2] := -5;
Matr[1][3] := 7;
Matr[2][0] := 6;
Matr[2][1] := 5;
Matr[2][2] := 4;
Matr[2][3] := -2;
Matr[3][0] := 1;
Matr[3][1] := 6;
Matr[3][2] := 7;
Matr[3][3] := -5;
out := ' 1 5 -5 4';
TestMod(Matr,razm,out,3);
end;




BEGIN
test1();
test2();	
test3();
	
END.
