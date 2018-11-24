clear;

%%
%打开文件TXT
fid=fopen('累计IMF20150610 163202.txt');
x1=fscanf(fid,'%f');
N1=length(x1);
fs = 200;
sample1 = 200;
sample=200*1000000;
%画原始数据　
tx1=1:N1;
figure;
plot(tx1,x1,'--*r');
title('lele');
grid on;
%原始数据做FFT
x11=x1(400:1700);
%%%%%%%%

t1 = 1:length(x11);

xx2 = hanning(length(x11));
% x2 = hanning(length(x1));     
% x3 = boxcar(length(x1));     
% x4 = chebwin(length(x1),20);     
% x5 = bartlett(length(x1));

x2 = x11.*xx2;

figure; 
% stem(t,imf(2,:),'k','.','LineWIdth',1.5);
plot(t1,x2,'r','LineWIdth',1.5);
grid on;

NFFT = 2^nextpow2(length(x2))*16;

% xy2 = hanning(NFFT);

AA1 = abs(fft(x2,NFFT))*2/NFFT;
AA = AA1;

f = fs/2*linspace(0,1,NFFT/2)+fs*16/NFFT;

figure;
% stem(f,AA(1:NFFT/2),'.');
stem(f,AA(1:NFFT/2),'.');
axis([0,10,0,1.1*max(AA(1:NFFT/2))]);
grid on;
hold on;
y2 = ones(1,NFFT/2)*max(AA(1:NFFT/2))*(10^(6/(-20)));
plot(f,y2,'r','LineWidth',2);
axis([0,10,0,1.1*max(AA(1:NFFT/2))]);


%%%%%
% N11=length(x11);
% y22latefft = fft(x11,N11);
% mag22=abs(y22latefft);
% ty22=0:N11-1;
% tty22=ty22*sample/N11;
% %figure(2);
% %plot(tty22,mag22,'--*r');
% 
% max22=max(mag22)/2;
% tymax22=0:1:N11-1;
% ttymax22=tymax22*sample/N11;
% figure(2);
% plot(tty22,mag22,'--*r',ttymax22,max22,'--*g');
% title('lele');
% axis([0,6000000,0,40]);
% xlabel('频率/Hz');
