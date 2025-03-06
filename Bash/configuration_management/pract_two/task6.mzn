% переменные для версий пакетов: major, minor, patch
array[1..3] of var 0..10: root_version;   % root [major, minor, patch]
array[1..3] of var 0..10: foo_version_1_1_0;   % foo 1.1.0
array[1..3] of var 0..10: foo_version_1_0_0;   % foo 1.0.0
array[1..3] of var 0..10: left_version;   % left 1.0.0
array[1..3] of var 0..10: right_version;  % right 1.0.0
array[1..3] of var 0..10: shared_version_2_0_0; % shared 2.0.0
array[1..3] of var 0..10: shared_version_1_0_0; % shared 1.0.0
array[1..3] of var 0..10: target_version_2_0_0; % target 2.0.0
array[1..3] of var 0..10: target_version_1_0_0; % target 1.0.0

% oграничения для root
constraint 
    % root 1.0.0 зависит от foo ^1.0.0 и target ^2.0.0.
    (foo_version_1_0_0[1] == 1 /\ foo_version_1_0_0[2] >= 0 /\ foo_version_1_0_0[2] < 2) /\
    (target_version_2_0_0[1] == 2 /\ target_version_2_0_0[2] >= 0);

% oграничения для foo 1.1.0
constraint 
    % foo 1.1.0 зависит от left ^1.0.0 и right ^1.0.0.
    (left_version[1] == 1 /\ left_version[2] >= 0) /\
    (right_version[1] == 1 /\ right_version[2] >= 0);

% oграничения для left 1.0.0
constraint 
    % left 1.0.0 зависит от shared >=1.0.0.
    (shared_version_1_0_0[1] == 1 /\ shared_version_1_0_0[2] >= 0);

% oграничения для right 1.0.0
constraint 
    % right 1.0.0 зависит от shared <2.0.0.
    (shared_version_1_0_0[1] == 1 /\ shared_version_1_0_0[2] < 2);

% shared 1.0.0 зависит от target ^1.0.0
constraint 
    (target_version_1_0_0[1] == 1 /\ target_version_1_0_0[2] >= 0 /\ target_version_1_0_0[2] < 2);

% целевая функция
solve satisfy;
