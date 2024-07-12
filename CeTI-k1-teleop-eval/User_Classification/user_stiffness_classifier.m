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
    %user_number = size(username_list, 1);
   

%% Writing the path for every user
for m=1:size(username_list, 1)
    username = ['\' username_list(m)];
    end_file = '.csv';
    fileName_stiff_path = [dataset_path  username '_stiffness_answers' end_file];
    fileName_stiff(m) =  fileName_stiff_path(1)+fileName_stiff_path(2)+fileName_stiff_path(3)+fileName_stiff_path(4)+fileName_stiff_path(5);
    fileName_paint_path = [dataset_path  username '_paint_answers' end_file];
    fileName_paint(m) =  fileName_paint_path(1)+fileName_paint_path(2)+fileName_paint_path(3)+fileName_paint_path(4)+fileName_paint_path(5);
end
%% Reading the path with csvread and readtable
for m=1:size(username_list, 1)
    [filepath,name,ext] = fileparts(fileName_stiff(m));
    csv_stiff = csvread(fileName_stiff(m),1);
    csv_paint = csvread(fileName_paint(m),1);
%     table_stiff = readtable(fileName_stiff(m));   
%     table_stiff(1:size(csv_stiff,1),["ForceDeadbandParameter","VelocityDeadbandParameter","ForceDelay","CommandDelay","RefStiffness","YellowStiffnessValue"])
    %     table_paint = readtable(fileName_paint(m));

%% Writing data to txt files
    categories = ["ForceDeadband","VelocityDeadband","ForceDelay","CommandDelay","FlagVelocity",...
        "TDPAon","ReferenceStiffness","Repetition","EstimatedStiffness","Rating","Distortion","Accuracy","Difficulty"];

    txtfile_path = [username_list(m) '_stiffness.txt'];
    txtfile(m) =  txtfile_path(1)+txtfile_path(2);
    fileid = fopen(txtfile(m),'w');
    fprintf(fileid, '%s   %s  %s    %s    %s    %s\t  %s  %s   %s   %s          %s      %s\t%s\n', categories);
    for k=1:size(csv_stiff,1)
        fprintf(fileid, '%f\t%f\t  %f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t \n', csv_stiff(k,:));
    end
    fclose(fileid);
    %% Saving the data in structs
    stiffness(m).csv_stiff = csv_stiff;
    paint(m).csv_paint = csv_paint;
end

%% Assigning values to parameters
%%% Stiffness Task

for m=1:size(username_list, 1)
    %for n=1:size(csv_stiff,2)

    f_deadband_s = stiffness(m).csv_stiff(:,1);
    v_deadband_s = f_deadband_s(:,1);
    f_delay_s = stiffness(m).csv_stiff(:,3);
    c_delay_s = stiffness(m).csv_stiff(:,4);
    flag_vel_s = stiffness(m).csv_stiff(:,5);
    tdp_s = stiffness(m).csv_stiff(:,6);
    ref_stiffness = stiffness(m).csv_stiff(:,7);
    user_stiffness = stiffness(m).csv_stiff(:,8);
    rating_s = stiffness(m).csv_stiff(:,size(csv_stiff,2)-2);
    accuracy_s = stiffness(m).csv_stiff(:,size(csv_stiff,2)-1);
    difficulty_s = stiffness(m).csv_stiff(:,size(csv_stiff,2));

    x = 1:size(f_deadband_s, 1);
    username_list(1:m);
    [n,p]=size(stiffness(m).csv_stiff);
    t = 1:n;

    %% Assigning values to cell arrays
    Info.(sprintf('User_stiff_%d', m)) = {stiffness(m).csv_stiff(:,1), stiffness(m).csv_stiff(:,3),...
    stiffness(m).csv_stiff(:,7), stiffness(m).csv_stiff(:,8), stiffness(m).csv_stiff(:,9),...
    size(csv_stiff,1), username_list(m)};

    %         s(m).f_deadband_s(:,1) = stiffness(m).csv_stiff(:,1);
    %         s(m).v_deadband_s(:,2) = s(m).f_deadband_s(:,1);
    %         s(m).f_delay_s(:,3) = stiffness(m).csv_stiff(:,3);
    %         s(m).c_delay_s(:,4) = stiffness(m).csv_stiff(:,4);
    %         s(m).flag_vel_s(:,5) = stiffness(m).csv_stiff(:,5);
    %         s(m).tdp_s(:,6) = stiffness(m).csv_stiff(:,6);
    %         s(m).ref_stiffness(:,7) = stiffness(m).csv_stiff(:,7);
    %         s(m).actual_stiffness(:,8) = stiffness(m).csv_stiff(:,8);
    %         s(m).rating_s(:,9) = stiffness(m).csv_stiff(:,size(csv_stiff,2)-2);
    %         s(m).accuracy_s(:,10) = stiffness(m).csv_stiff(:,size(csv_stiff,2)-1);
    %         s(m).difficulty_s(:,11) = stiffness(m).csv_stiff(:,size(csv_stiff,2));
    %     %end

    %%% Paint Task
    %for n=1:size(csv_paint,2)
    %     p(m).f_deadband_p(:,1) = paint(m).csv_paint(:,1);
    %     p(m).v_deadband_p(:,2) = p(m).f_deadband_p(:,1);
    %     p(m).f_delay_p(:,3) = paint(m).csv_paint(:,3);
    %     p(m).c_delay_p(:,4) = p(m).f_delay_p(:,1);
    %     p(m).flag_vel_p(:,5) = paint(m).csv_paint(:,5);
    %     p(m).tdp_p(:,6) = paint(m).csv_paint(:,6);
    %     p(m).rating_p(:,7) = paint(m).csv_paint(:,size(csv_paint,2)-2);
    %     p(m).accuracy_p(:,8) = paint(m).csv_paint(:,size(csv_paint,2)-1);
    %     p(m).difficulty_p(:,9) = paint(m).csv_paint(:,size(csv_paint,2));

end


%% Clear temporary variables
clearvars filename end_file ext Files Files_ k m n p name username x ans;
%% Plotting


for m=1:size(username_list, 1)
    figure
%     subplot(2,2,m)
    for n=1:size(csv_stiff,2)
        %plot(t,stiffness(m).csv_stiff(:,1:4),'LineWidth', 1.5);
        hold on;
        plot(t,stiffness(m).csv_stiff(:,7:11),'LineWidth', 1.5);

        %         plot(x, f_deadband_s,'LineWidth', 1.5);
        %         hold on;
        %         plot(x, f_delay_s,'LineWidth', 1.5);
        %         hold on;
        %         plot(x, ref_stiffness,'LineWidth', 1.5);
        %         hold on;
        %         plot(x, actual_stiffness,'LineWidth', 1.5);

        %legend('f_{deadband}','v_{deadband}','f_{delay}','c_{delay}')
        title(username_list(m) + ' Answers')
        xlabel('Number of Tests')
        ylabel('Value')
    end
%     plot(t,stiffness(m).csv_stiff(:,8),'LineWidth', 1.5);
%     hold on;
%     title('User Stiffness Answers')
%     xlabel('User given stiffness values')
%     ylabel('Value')

end
    hold on; grid on;
    legend('user stiffness','reference stiffness','rating_s','accuracy_s','difficulty_s', 'Location','northeast')
    