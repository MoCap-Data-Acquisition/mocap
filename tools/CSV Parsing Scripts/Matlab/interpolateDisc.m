function newData=interpolateDisc(filename, deltaT)

data = csvread(filename,1);
sortedData = sortrows(data,4);
% trying to show good practices by using vectorized function rather than
% loops
partitionedData = arrayfun(@(x) sortedData(sortedData(:,1) == x, :), unique(sortedData(:,1)), 'uniformoutput', false);
% ummm this does a thing
pieces = {};
for i=1:size(partitionedData,1)
    pieces{i} = arrayfun(@(x) partitionedData{i}(partitionedData{i}(:,5) == x, :), unique(partitionedData{i}(:,5)), 'uniformoutput', false);
end
newData = {};
for i=1:size(pieces,1)
    tempData = {};
    for j=1:size(pieces{i},1)
        d = pieces{i}{j};
        newT = (d(1,4)-mod(d(1,4),deltaT):deltaT:d(end,4))';
        tempData{j}(:,1) = interp1(d(:,4), d(:,2), newT, 'spline');
        tempData{j}(:,2) = interp1(d(:,4), d(:,3), newT, 'spline');
        tempData{j}(:,3) = newT;
    end
    newData{i} = vertcat(tempData{:});
end