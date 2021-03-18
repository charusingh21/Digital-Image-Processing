I = readraw('Dogs.raw');
c=481;
r=321;
k=1;
for i=1:r
    for j=1:c
        rc(i,j)=I(k);
        gc(i,j)=I(k+1);
        bc(i,j)=I(k+2);
        k=k+3;
    end
end
w=0.2989*rc +0.587*gc+ 0.114*bc;
out=edge(w,'canny',[0 0.1]);
writeraw (out,'cannyres');