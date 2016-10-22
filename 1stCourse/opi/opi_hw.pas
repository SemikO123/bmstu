{$INCLUDE directive.txt}
unit opi_hw;

interface
{
Матрица - двумерный массив  
}
type matrix = array of array of integer;

 {
 Ввод матрицы
 @param(n Целое число, размерность матрицы)
 } 

function InputMatrix(n:integer):matrix;

{
Поиск диагонали матрицы, параллельной главной, с наибольшей суммой положительных элементов 
@param(A Матрица элементов)
@param(t Целое число, размерность матрицы)
@return(Строка с текстом для печати)
}

function MaxSummaDiag(A:matrix; t:integer):string;

{
Поиск диагонали матрицы, параллельной побочной, с наименьшим произведением отрицательных элементов 
@param(A Матрица элементов)
@param(t Целое число, размерность матрицы)
@return(Строка с текстом для печати)
}

function MinMultiplDiag(A:matrix; t:integer):string;

implementation

function InputMatrix(n:integer):matrix;
var i,j,z:integer;
begin
i := -1;
SetLength(InputMatrix,n);
for z:= 0 to n-1 do
SetLength(InputMatrix[z],n);
writeln('Введите матрицу построчно, разделяя элементы пробелами:');
while i < n-1 do
  begin
    i := i+1;
    j := -1;
    while j < n-1 do
      begin
        j := j+1;
        read(InputMatrix[i][j]);
      end;
  end;

end;

function MaxSummaDiag(A:matrix; t:integer):string;
var maxsum,maxi,count,i,m,n,j,sum,c: integer;
    mass,ss : string; 
    
begin
maxsum := 0;
mass := '';
maxi := -t;
count := 0;
i := 1 - t;
for m:=0 to t-1 do
  for n:=0 to t-1 do
    if A[m][n] <= 0 then
      count := count + 1;
if count < t*t then
  begin 
  while i <= t-1 do
    begin
      sum := 0;
      if i <= 0 then 
        j := 0
      else
        j := i;
      while (j-i < t) and ( j < t) do
        begin
          if A[j-i][j] > 0 then
            sum := sum + A[j-i][j];
          j := j + 1;
        end;
      if (sum > maxsum) or (i = 1 -t) then
        begin
          maxsum := sum;
          maxi := i;
        end;
      i := i + 1;
    end;
  if maxi <= 0 then
    j := 0
  else 
    j := maxi;
  c := 0;
  while (j - maxi <  t) and (j < t) do
    begin
      c := c + 1;
      str(A[j-maxi][j],ss);
      mass := mass + ' ' + ss;
      j := j + 1;
    end;
    Result := mass;
    end
  else
    Result := 'Нет положительных элементов';
end;


function MinMultiplDiag(A:matrix; t:integer):string;
var minmult,mini,count,i,m,n,j,mult,c,k: integer;
    mass,ss : string; 
    
begin
minmult := 0;
mass := '';
mini := -t;
count := 0;
i := 1 - t;
for m:=0 to t-1 do
  for n:=0 to t-1 do
    if A[m][n] >= 0 then
      count := count + 1;
if count < t*t then
  begin 
  while i <= t-1 do
    begin
      mult := 1;
      if i <= 0 then
        begin
        j := 0;
        k := t - 1;
        end
      else
        begin
        j := i;
        k := t - i - 1;
        end;
      while (j-i < t) and ( j < t) do
        begin
          if A[i+k][j] < 0 then
            mult := mult * A[i+k][j];
          j := j + 1;
          k := k - 1;
        end;
      if (mult < minmult) or (i = 1 -t) then
        begin
          minmult := mult;
          mini := i;
        end;
      i := i + 1;
    end;
  if mini <= 0 then
    begin
    j := 0;
    k := t - 1;
    end
  else 
    begin
    j := mini;
    k := t - mini - 1;
    end;
  c := 0;
  while (j - mini <  t) and (j < t) do
    begin
      c := c + 1;
      str(A[mini+k][j],ss);
      mass := mass + ' ' + ss;
      j := j + 1;
      k := k - 1;
    end;
    Result := mass;
    end
  else
    Result := 'Нет отрицательных элементов';
end;
end.