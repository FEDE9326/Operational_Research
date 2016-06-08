Y=[rand(1:3) heu(1:3) rand(7:9) heu(7:9) rand(10:12) heu(10:12)]
close all

grid on
figure
bar3(Y(:,1:2))
%bar3(Y,'Stacked')
%hold on
%Y=[rand(7:9) heu(7:9)]
%bar3(Y,'Stacked')
%hold on

%Y=[rand(10:12) heu(10:12)]
%bar3(Y,'Stacked')
%hold on