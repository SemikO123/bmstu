program sort;

uses crt, SysUtils, DateUtils;

const n1 = 30000;
      names:array[1..9] of string=('Иван','Петр','Максим','Алексей','Евгений','Даниил','Сергей','Павел','Никита');
      cities:array[1..8] of string=('Москва','Санкт-Петербург','Казань','Самара','Волгоград','Екатеринбург','Саратов','Тверь');
      works:array[1..7] of string=('менеджер','продавец','банкир','программист','управляющий','инженер','водитель');
type massiv = array [1..n1] of integer;

     infmass = Record
        num:integer;
        name:string;
        city:string;
        work:string;
        end;
        
    massivinf = array[1..n1] of infmass;
        
       

procedure ShakerSort(var A:massiv; cou:integer);
var l, r, i, x: Integer;
BEGIN
  l := 1;
  r := cou;
  while l <= r do
    begin
      for i := l to r do
        if A[i+1] > A[i] then
          begin
            x := A[i+1];
            A[i+1] := A[i];
            A[i] := x;
            r := i+1;
          end;
      r := r - 1;
      for i := r downto l do
        if A[i-1] > A[i] then
          begin
            x := A[i];
            A[i] := A[i-1];
            A[i-1] := x;
            l := i-1;
          end;
       l := l + 1;
     end;
END;

procedure InfShakerSort(var A:massivinf; cou:integer);
var l, r, i: Integer;
    x : infmass;
BEGIN
   l := 1;
  r := cou;
  while l <= r do
    begin
      for i := l to r do
        if A[i+1].num > A[i].num then
          begin
            x := A[i+1];
            A[i+1] := A[i];
            A[i] := x;
            r := i+1;
          end;
      r := r - 1;
      for i := r downto l do
        if A[i-1].num > A[i].num then
          begin
            x := A[i];
            A[i] := A[i-1];
            A[i-1] := x;
            l := i-1;
          end;
       l := l + 1;
     end;
END;



procedure MassRand(var A:massiv;k:integer); 
var i:integer;
BEGIN
Randomize;
for i:=1 to k do
  A[i] := random(100); 
END;

procedure MassUp(var A:massiv; k:integer);
var i:integer;
BEGIN
for i:=1 to k do
  A[i] := i;
END;

procedure MassDown(var A:massiv; k:integer);
var i:integer;
BEGIN
for i:=1 to k do
  A[i] := k-i;
END;

procedure InfMassUp(var A:massivinf; k:integer);
var i:integer;
BEGIN
for i:=1 to k do
  begin
    A[i].num := i;
    A[i].name := names[(i mod 9)+1];
    A[i].city := cities[(i mod 8)+1];
    A[i].work := works[(i mod 7)+1];
  end;
END;

procedure InfMassDown(var A:massivinf; k:integer);
var i:integer;
BEGIN
for i:=1 to k do
  begin
    A[i].num := k-i;
    A[i].name := names[(i mod 9)+1];
    A[i].city := cities[(i mod 8)+1];
    A[i].work := works[(i mod 7)+1];
  end;
END;

procedure InfMassRand(var A:massivinf; k:integer);
var i:integer;
BEGIN
randomize;
for i:=1 to k do
  begin
    A[i].num := random(n1);
    A[i].name := names[(i mod 9)+1];
    A[i].city := cities[(i mod 8)+1];
    A[i].work := works[(i mod 7)+1];
  end;
END;


var  start, finish, t1,t2,t3: TDateTime;
     i, n:integer;
     A: massiv;
     B: massivinf;

BEGIN
begin
n := n1 div 1000;
writeln('Время работы Шейкер-сортировки (мс)');
writeln('Количество':10,'|','Упорядоченный':14,'|','Случайный':14,'|','Убыв.':5);
writeln(' элементов':10,'|','   массив    ':14,'|','  массив ':14,'|','массив':5);
writeln('------------------------------------------');
for i:=1 to 4 do
begin
n := n*5;
MassUp(A,n);
start := Now;
ShakerSort(A,n);
finish := Now;
t1 := SecondOf(finish-start)*1000+MillisecondOf(finish-start);

MassRand(A,n);
start := Now;
ShakerSort(A,n);
finish := Now;
t2 := SecondOf(finish-start)*1000+MillisecondOf(finish-start);

MassDown(A,n);
start := Now;
ShakerSort(A,n);
finish := Now;
t3 := SecondOf(finish-start)*1000+MillisecondOf(finish-start);
Writeln(n:10,'|',t1:13:0,'|',t2:9:0,'|',t3:5:0);
end;
end;


begin
n := n1 div 1000;
writeln('');
writeln('Время работы c доп.информацией(мс)');
writeln('Доп.информация вида:"55  Иван  Москва  банкир"');
writeln('Количество':10,'|','Упорядоченный':14,'|','Случайный':14,'|','Убыв.':5);
writeln(' элементов':10,'|','   массив    ':14,'|','  массив ':14,'|','массив':5);
writeln('------------------------------------------');
for i:=1 to 4 do
begin
n := n*5;
InfMassUp(B,n);
start := Now;
InfShakerSort(B,n);
finish := Now;
t1 := SecondOf(finish-start)*1000+MillisecondOf(finish-start);

InfMassRand(B,n);
start := Now;
InfShakerSort(B,n);
finish := Now;
t2 := SecondOf(finish-start)*1000+MillisecondOf(finish-start);

InfMassDown(B,n);
start := Now;
InfShakerSort(B,n);
finish := Now;
t3 := SecondOf(finish-start)*1000+MillisecondOf(finish-start);

Writeln(n:10,'|',t1:13:0,'|',t2:9:0,'|',t3:5:0);
end;
end;

//readln;

END.


