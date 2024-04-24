; ModuleID = 'amukh'
source_filename = "amukh"

@0 = private unnamed_addr constant [15 x i8] c"Hello, World!\0A\00", align 1

declare void @printf(i8*)

define void @main() {
entry:
  call void @printf(i8* getelementptr inbounds ([15 x i8], [15 x i8]* @0, i32 0, i32 0))
  ret void
}
