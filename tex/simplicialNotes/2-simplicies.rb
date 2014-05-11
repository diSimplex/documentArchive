#!/usr/bin/ruby

# this ruby script builds Tikz pictures of 2-simplicies


def buildA2Simplex(outFile, ab1, bc1, ac1, ab2, bc2, ac2)

abArr = (ab1==1) ? "->" : "<-";
bcArr = (bc1==1) ? "->" : "<-";
acArr = (ac1==1) ? "->" : "<-";

ends = [ "[>-]", "", "[<-]"];

outFile.puts("\\begin{cTikzPicture}");
outFile.puts("\\coordinate (O) at (0,0);");
outFile.puts("\\coordinate (A) at (0,1);");
outFile.puts("\\coordinate (B) at ($ (O)!1cm!120:(A) $);");
outFile.puts("\\coordinate (C) at ($ (O)!1cm!-120:(A) $);");
outFile.puts("");
outFile.puts("\\fill (A) circle[radius=1pt];");
outFile.puts("\\fill (B) circle[radius=1pt];");
outFile.puts("\\fill (C) circle[radius=1pt];");
outFile.puts("");
outFile.puts("\\begin{scope}[shorten >=4pt, shorten <=4pt]");
outFile.puts("\\path (A) edge[#{abArr}] node (AB) {} (B);");
outFile.puts("\\path (B) edge[#{bcArr}] node (BC) {} (C);");
outFile.puts("\\path (A) edge[#{acArr}] node (AC) {} (C);");
outFile.puts("\\end{scope}");
outFile.puts("");
outFile.puts("\\begin{scope}[shorten <=4pt]");
outFile.puts("\\path (AB) edge#{ends[ab2]} (O);");
outFile.puts("\\path (BC) edge#{ends[bc2]} (O);");
outFile.puts("\\path (AC) edge#{ends[ac2]} (O);");
outFile.puts("\\end{scope}");
outFile.puts("");
outFile.puts("\\node[above]       at (A) {a};");
outFile.puts("\\node[below left]  at (B) {b};");
outFile.puts("\\node[below right] at (C) {c};");
outFile.puts("");
#outFile.puts("\\node[above left]  at (AB) {$d^2_#{ab2}$};");
#outFile.puts("\\node[left=6pt]    at (A)  {$d^1_#{1-ab1}$};");
#outFile.puts("\\node[above left]  at (B)  {$d^1_#{ab1}$};");
#outFile.puts("");
#outFile.puts("\\node[below]       at (BC) {$d^2_#{bc2}$};");
#outFile.puts("\\node[below right] at (B) {$d^1_#{1-bc1}$};");
#outFile.puts("\\node[below left]  at (C) {$d^1_#{bc1}$};");
#outFile.puts("");
#outFile.puts("\\node[above right] at (AC) {$d^2_#{ac2}$};");
#outFile.puts("\\node[right=6pt]   at (A) {$d^1_#{1-ac1}$};");
#outFile.puts("\\node[above right] at (C) {$d^1_#{ac1}$};");
outFile.puts("\\end{cTikzPicture}");

end

def cycleThrough2SimplexOrientations(outFile, ab1, bc1, ac1)

allChoices = [0, 1, 2];

allChoices.each() { | ab2 |
  otherChoices = allChoices.select{ | i | i != ab2; };  
  otherChoices.each() { | bc2 |
    lastChoice = otherChoices.select{ | j | j !=bc2; };
    ac2 = lastChoice[0];
#    puts "ab:#{ab2} bc:#{bc2} ac:#{ac2}";
    buildA2Simplex(outFile, ab1, bc1, ac1, ab2, bc2, ac2);
  }
}

end


def cycleThrough1SimplexOrientations(outFile) 
  2.times() { | ab1 |
    2.times() { | bc1 |
      2.times() { | ac1 |
        cycleThrough2SimplexOrientations(outFile, ab1, bc1, ac1);
      }
    }
  }
end


outFile = File.open("test.tex", "w");

cycleThrough1SimplexOrientations(outFile);

outFile.close();
