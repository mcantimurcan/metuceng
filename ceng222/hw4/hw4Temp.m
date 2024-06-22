N = 4145;
lambdaA = 60;  % number of automobiles
lambdaT = 12;  % number of trucks

alphaA = 120; lambdaA_2 = 0.1; % Gamma distribution lambda
alphaT = 14; lambdaT_2 = 0.001;

TotalWeight = zeros(N, 1); % a vector that keeps the total weight for each Monte Carlo run
for k = 1:N;
  % first generate the number of passed vehicles for each type from Poisson
  numA = 0;
  numT = 0;

  % number of automobiles
  U = rand;
  F = exp(-lambdaA);
  while (U >= F);
    numA = numA + 1;
    F = F + exp(-lambdaA) * lambdaA ^ numA/gamma(numA + 1);
  end;

  % number of trucks
  U = rand;
  F = exp(-lambdaT);
  while (U >= F);
    numT = numT + 1;
    F = F + exp(-lambdaT) * lambdaT ^ numT/gamma(numT + 1);
  end;

	weight = 0; % total weight of vehicles for this run

  % calculate the total weight of automobiles
  weightA = 0;
	for j=1:numA;
		weightA = weightA + sum(-1/lambdaA_2 * log(rand(alphaA, 1)));
	end;

  % calculate the total weight of trucks
  weightT = 0;
	for j=1:numT;
		weightT = weightT + sum(-1/lambdat_2 * log(rand(alphaT, 1)));
	end;

  weight = weightA + weightT;
	TotalWeight(k) = weight;
end;

p_est = mean(TotalWeight>250000);
expectedWeight = mean(TotalWeight);
stdWeight = std(TotalWeight);

fprintf('Estimated probability = %f\n',p_est);
fprintf('Expected weight = %f\n',expectedWeight);
fprintf('Standard deviation = %f\n',stdWeight);
