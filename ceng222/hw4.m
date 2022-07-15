N=4147;      
an_lambda = 50; 
tn_lambda = 10;
aw_lambda = 0.15; aw_alpha = 190;
tw_lambda = 0.01; tw_alpha = 110;
totalWeight=zeros(N,1); 

for k=1:N;

	aw=calculateweight(an_lambda,aw_lambda,aw_alpha);
  tw=calculateweight(tn_lambda,tw_lambda,tw_alpha);
  totalWeight(k) = aw+tw;

end;

p_est = mean(totalWeight>200000);
expectedWeight = mean(totalWeight);
stdWeight = std(totalWeight);

fprintf('Estimated probability = %f\n',p_est);
fprintf('Expected weight = %f\n',expectedWeight);
fprintf('Standard deviation = %f\n',stdWeight);

function weight=calculateweight(n_lambda,w_lambda,w_alpha)
    U = rand; i = 0; 
    F = exp(-n_lambda);
    while (U>=F);
		i=i+1;
		F = F+exp(-n_lambda)*n_lambda^i/gamma(i+1);
    end;
    weight=sum(sum(-1/w_lambda * log(rand(w_alpha, i))));
end