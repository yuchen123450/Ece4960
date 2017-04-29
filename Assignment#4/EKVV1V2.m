% for i=0:51
z = x(7,:) * 10^9;
% end


% plot V1
figure;
t=0:0.2:99.8;
plot(t,x(1,:));
xlabel('time(ns)');
ylabel('Voltage');
hold on;

plot(t,x(3,:));
hold on;
grid on;
plot(z(1:25),x(5,1:25));
legend('forward euler','RK34','RK34 adaptive');
title('V1 value in EKV Circuit');

% plot V2
figure;
plot(t,x(2,:));
xlabel('time(ns)');
ylabel('Voltage');
hold on;

plot(t,x(4,:));
hold on;
grid on;

plot(z(1:25),x(6,1:25));
legend('forward euler','RK34','RK34 adaptive');
title('V2 value in EKV Circuit');