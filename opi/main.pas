uses opi_hw;
var A:opi_hw.matrix;
    razm,i:integer;
    mx,mn : string;

begin
writeln('Введите размерность матрицы:');
read(razm);
if razm <= 0 then
  writeln('Некорректно задана размерность матрицы')
else
  begin
    SetLength(A,razm);
    for i:=0 to razm-1 do
      SetLength(A[i],razm);
    A := InputMatrix(razm);
    mx := MaxSummaDiag(A,razm);
    if mx <> 'Нет положительных элементов' then
    writeln('Диагональ с максимальной суммой положительных элементов',mx)
    else writeln(mx);
    mn := MinMultiplDiag(A,razm);
    if mn <> 'Нет отрицательных элементов' then
    writeln('Диагональ с минимальным произведением отрицательных элементов',mn)
    else writeln(mn);
  end;
 end.