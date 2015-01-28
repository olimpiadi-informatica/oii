program pesca;
const MAX_P =  1000000;
var input, output   : text;
   p                : longint; // punti pescosi.
   n_pescosi        : longint; // numero di punti pescosi nella rete.
   start_x, start_y : longint; // coordinate di partenza delle barche;
   min_x, min_y     : longint;
   x                : array[1..MAX_P] of longint;
   y                : array[1..MAX_P] of longint;
   taken            : array[1..MAX_P] of longint; // 1 = true, 0 =  false;
   i, j             : longint;
   cmd              : longint;

   procedure QuickSortRecur(start, stop, mode: longint);
            var  splitPt: longint;

            { The quicksort split function takes the range,
              and returns the split point. }
            function Split(start, stop, mode: longint): longint;
                var left, right: longint;       { Scan pointers. }
                    pivot: longint;             { Pivot value. }

                procedure swap(var a, b: longint);
                    var tmp: longint;
                    begin
                        tmp := a; a := b; b := tmp
                    end;

               function isLess(pos1, pos2, mode : longint ): boolean;
               begin
                  isLess := false;
                  if (mode = 0) then
                  begin
                     if x[pos1] < x[pos2] then isLess := true;
                     if (x[pos1] = x[pos2]) and (y[pos1] < y[pos2]) then isLess := true;
                  end
                  else // mode = 1
                  begin
                     if y[pos1] < y[pos2] then isLess := true;
                     if (y[pos1] = y[pos2]) and (x[pos1] < x[pos2]) then isLess := true;
                  end
               end;

                begin
                    { Set up the pointers for the hight and low sections, and
                      get the pivot value. }
                    swap( x[start], x[(start+stop) div 2] );
                    swap( y[start], y[(start+stop) div 2] );
                    swap( taken[start], taken[(start+stop) div 2] );
                    pivot := start;
                    left := start + 1;
                    right := stop;

                    { Look for pairs out of place and swap 'em. }
                    while left <= right do
                    begin
                        while (left <= stop) and isLess(left,pivot, mode) do
                            left := left + 1;
                        while (right > start) and (not isLess(right, pivot, mode) ) do
                            right := right - 1;
                        if left < right then
                        begin
                            swap(x[left], x[right]);
                            swap(y[left], y[right]);
                            swap(taken[left], taken[right]);
                        end;
                    end;

                    { Put the pivot between the halves. }
                    swap(x[start], x[right]);
                    swap(y[start], y[right]);
                    swap(taken[start], taken[right]);

                    Split := right
                end;

            begin { QuickSortRecur }
                if start < stop then
                begin
                    splitPt := Split(start, stop, mode);
                    QuickSortRecur(start, splitPt-1, mode);
                    QuickSortRecur(splitPt+1, stop, mode);
                end
            end;


// 0 incrementa la y
// 1 incrementa la x

begin
   ReadLn(p);
   ReadLn(start_x, start_y);
   for i := 1 to p do
   begin
      ReadLn(x[i], y[i]);
      taken[i] := 1;
   end;

   {for i := 1 to p do
      WriteLn(x[i], ' ', y[i]);}

   for j := 1 to 2 do   // le navi sono due
   begin
      Read(cmd);
      if(cmd < 0) then
      begin  // pilotiamo la nave bassa
         QuickSortRecur(1, p, 0);  // prima chiave: x, seconda chiave: y

         {for i := 1 to p do
             WriteLn(x[i], ' ', y[i]);}

         i := 1;
         while(i<=p) and (x[i] < start_x) do
         begin
            taken[i] := 0;
            { WriteLn('Ho tagliato il punto ', x[i], ' ', y[i]); }
            i := i+1;
         end;

         min_x := start_x;
         min_y := start_y;
         while cmd <> 0 do
         begin
            if(cmd<0) then
            begin
               min_x := min_x -cmd;
               while(i<=p) and (x[i] <= min_x) do
               begin
                  if y[i]< min_y then
                  begin
                     { WriteLn('Ho tagliato il punto ', x[i], ' ', y[i]); }
                     taken[i] := 0;
                  end;
                  i := i+1;
               end;
            end
            else  min_y := min_y +cmd;
            Read(cmd);
         end;
         while(i<=p) do
         begin
             if x[i] > min_x then
             begin
                { WriteLn('Ho tagliato il punto ', x[i], ' ', y[i]); }
                taken[i] := 0;
             end;
             i := i+1;
         end;
      end
      else
      begin  // pilotiamo la nave alta
         QuickSortRecur(1, p, 1);   // prima chiave: y, seconda chiave: x

         {for i := 1 to p do
             WriteLn(x[i], ' ', y[i]);}

         i := 1;
         while(i<=p) and (y[i] < start_y) do
         begin
            taken[i] := 0;
            { WriteLn('Ho tagliato il punto ', x[i], ' ', y[i]); }
            i := i+1;
         end;

         min_x := start_x;
         min_y := start_y;
         while cmd <> 0 do
         begin
            if(cmd<0) then
            begin
               min_x := min_x -cmd;
               Read(cmd);
            end
            else
            begin
               repeat
                  min_y := min_y +cmd;
                  Read(cmd);
               until (cmd<=0);
               while(i<=p) and (y[i] <= min_y) do
               begin
                  if x[i]< min_x then
                  begin
                     { WriteLn('Ho tagliato il punto ', x[i], ' ', y[i]); }
                     taken[i] := 0;
                  end;
                  i := i+1;
               end;
            end;
         end;
         while(i<=p) do
         begin
             if y[i] > min_y then
             begin
                { WriteLn('Ho tagliato il punto ', x[i], ' ', y[i]); }
                taken[i] := 0;
             end;
             i := i+1;
         end;
      end
   end;

   n_pescosi := 0;
   {WriteLn('I punti sono:');}
   for i := 1 to p do
      if taken[i] = 1  then
      begin
         n_pescosi := n_pescosi +1;
         { WriteLn(x[i], ' ', y[i]); }
      end;

   WriteLn(n_pescosi);
end.
