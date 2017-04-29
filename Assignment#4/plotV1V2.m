% for i=0:51
z = y(11,:) * 10^9;
% end


% plot V1
figure;
t=0:0.2:99.8;
plot(t,y(1,:));
xlabel('time(ns)');
ylabel('Voltage');
hold on;
for i=1:1:3
    plot(t,y(2*i+1,:));
    hold on;
end
grid on;
plot(z(1:51),y(9,1:51));
legend('backward euler','forward euler','trapezoidal','RK34','RK34 adaptive');
title('V1 value in Fig3');

% plot V2
figure;
plot(t,y(2,:));
xlabel('time(ns)');
ylabel('Voltage');
hold on;
for i=1:1:3
    plot(t,y(2*i+2,:));
    hold on;
end
grid on;
plot(z(1:51),y(10,1:51));
legend('backward euler','forward euler','trapezoidal','RK34','RK34 adaptive');
title('V2 value in Fig3');