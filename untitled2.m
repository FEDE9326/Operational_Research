clc
fmedioh20_4=mean(fh20_4);
fmedior20_a=mean(fr20_4);
fmedioh30_4=mean(fh30_4);
fmedior30_a=mean(fr30_4);
fmedioh40_4=mean(fh40_4);
fmedior40_a=mean(fr40_4);
data20=[fh20_4 fr20_4];
data30=[fh30_4 fr30_4];
data40=[fh40_4 fr40_4];
figure
bar(data20)
title 'N20 d4'
figure
bar(data30)
title 'N30 d4'
figure
bar(data40)
title 'N40 d4'