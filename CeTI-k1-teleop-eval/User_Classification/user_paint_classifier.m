clear all
close all
clc

dataset_path = 'C:\Users\Arsan\OneDrive\Desktop\ceti-k1-teleop-eval\GUI\SurveyUserAnswers';
%filename = '../GUI/SurveyUserAnswers';
%% Getting the file names and usernames from SurveryUserAnswers
Files_ = dir(dataset_path);
% for k=1:length(Files)
%    FileNames = Files(k).name;
% end
%disp(Files.name(3))
Files = struct2table(Files_);
display_names = Files(3:end,1);
display_names = table2array(display_names);
for k=1:(length(Files_)-2)
    unextracted_path(k) = extractBefore(display_names(k,1),"_");
    username_list(k) = string(unextracted_path(k));
    username_list = transpose(username_list);
end
%% Deleting the duplicate names
    username_list = unique(username_list);
   

%% Writing the path for every user
for m=1:size(username_list, 1)
    username = ['\' username_list(m)];
    end_file = '.csv';
    fileName_paint_path = [dataset_path  username '_paint_answers' end_file];
    fileName_paint(m) =  fileName_paint_path(1)+fileName_paint_path(2)+fileName_paint_path(3)+fileName_paint_path(4)+fileName_paint_path(5);
end
%% Reading the path with csvread and readtable
for m=1:size(username_list, 1)
    %[filepath,name,ext] = fileparts(fileName_stiff(m));
    csv_paint = csvread(fileName_paint(m),1);
    table_paint = readtable(fileName_paint(m));

%% Writing data to txt files
    categories = ["ForceDeadband","VelocityDeadband","ForceDelay","CommandDelay","FlagVelocity",...
        "TDPAon","Repetition","Rating","Distortion","Accuracy","Difficulty"];

    txtfile_path = [username_list(m) '_paint.txt'];
    txtfile(m) =  txtfile_path(1)+txtfile_path(2);
    fileid = fopen(txtfile(m),'w');
    fprintf(fileid, '%s   %s  %s    %s    %s    %s\t\t%s\t%s\t\t%s\t%s\t%s      \n', categories);
    for k=1:size(csv_paint,1)
        fprintf(fileid, '%f\t%f\t  %f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t \n', csv_paint(k,:));
    end
    fclose(fileid);
    %% Saving the data in structs
    paint(m).csv_paint = csv_paint;
end

%% Assigning values to parameters
%%% Stiffness Task

for m=1:size(username_list, 1)

    f_deadband_p = paint(m).csv_paint(:,1);
    v_deadband_p = f_deadband_p(:,1);
    f_delay_p = paint(m).csv_paint(:,3);
    c_delay_p = f_delay_p(:,1);
    flag_vel_p = paint(m).csv_paint(:,5);
    tdp_p = paint(m).csv_paint(:,6);
    rating_p = paint(m).csv_paint(:,size(csv_paint,2)-2);
    accuracy_p = paint(m).csv_paint(:,size(csv_paint,2)-1);
    difficulty_p = paint(m).csv_paint(:,size(csv_paint,2));

    x = 1:size(f_deadband_p, 1);
    username_list(1:m);
    [n,p]=size(paint(m).csv_paint);
    t = 1:n;

    %% Assigning values to cell arrays
    Info.(sprintf('User_paint_%d', m)) = {paint(m).csv_paint(:,1), paint(m).csv_paint(:,3),...
    paint(m).csv_paint(:,7), paint(m).csv_paint(:,8), paint(m).csv_paint(:,9),...
    size(csv_paint,1), username_list(m)};
end


%% Clear temporary variables
clearvars filename end_file ext Files Files_ k m n p name username x ans;
%% Plotting


for m=1:size(username_list, 1)
    figure
%     subplot(2,2,m)
    for n=1:size(csv_paint,2)
        hold on;
        plot(t,paint(m).csv_paint(:,7:11),'LineWidth', 1.5);
        title(username_list(m) + ' Answers')
        xlabel('Number of Tests')
        ylabel('Value')
    end

end
    hold on; grid on;
    %legend('user stiffness','reference stiffness','rating_p','accuracy_p','difficulty_p', 'Location','northeast')
    