function [Countries,CountriesNames,DataCumulative,DataDaily,Dates,States] = FetchData()
% FetchData Fetchs the data from covid_data mat file in the current directory
%   FetchData() calculates and returns the countries their names, Data
%   (both Daily and Cumulative) both as 3-d arrays, the Dates and the
%   States as map for different countries
    load covid_data.mat covid_data; % Loads the data
    country = covid_data(2:end,1);  % Get the country names
    Countries = ['Global';country]; % Add Global at the top
    s = ['All';covid_data(2:end,2)];        % Get all the States
    % Define States as a map like a dictionary in Python
    States = containers.Map;
    CountriesNames = ['Global';unique(country)]; % Unique Country names with Global at the top
    Dates = covid_data(1,3:end);    % All Dates in record
    % Define a variable for Cumulative Data of appropriate size
    % 3rd dimension is 2 for both Cases and Deaths
    DataCumulative = zeros(length(Dates),length(Countries),2);
    for i = 2:length(Countries)     % Fill except for Global
        temp = covid_data(i,3:end);
        DataCumulative(:,i,:) = cell2mat(temp');
    end
    c = zeros(1,length(CountriesNames)); % array for index of each country
    for i = 1:length(CountriesNames)
        c_index = find(string(Countries) == CountriesNames(i),1);
        s(c_index) = {'All'};       % Add All in State of each country
        c(i) = c_index;      % Store the indices to calculate Global Data
        % Stores States with country name as a variable
        States(char(CountriesNames(i))) = s(string(Countries) == CountriesNames(i));
    end
    % Only sum the total Data of each country
    DataCumulative(:,1,:) = sum(DataCumulative(:,c,:),2);
    % Define variable for Daily Data of size same as Cumulative Data
    DataDaily = zeros(size(DataCumulative));
    for i = length(DataDaily(:,1,1)):-1:2
        % To get Daily Data subtract rows in Cumulative Data from the end
        DataDaily(i,:,:) = DataCumulative(i,:,:) - DataCumulative(i-1,:,:);
    end
    % Store only the positive values
    DataDaily = DataDaily .* (DataDaily > 0);
end