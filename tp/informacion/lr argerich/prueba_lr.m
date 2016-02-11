load('lrset1.mat');
PlotClasses(lrset1,lrlabels1)
theta = GD(lrset1,lrlabels1,0.01,1000,0,@LRCost,@LRGradient);
PlotClasses(lrset1,lrlabels1,theta);

