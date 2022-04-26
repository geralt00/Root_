#!/bin/bash
#
#set +x
date=`date +%N`
test $# -lt 4 && echo $0 '<prefix_jobname> <job_num> <prefix_ecms> <ecms> <beam-e-s> <run1> <run2>' && exit 0
name=$1
num=$2
dir=$3
cms=$4
test $num -lt 1 && echo $2 less than 1 && exit 0
test -f sim_ini/run_template_head.txt || exit 0 
test -f sim_ini/run_template_tail.txt || exit 0 
test -f rec_ini/run_template_head.txt || exit 0 
test -f rec_ini/run_template_tail.txt || exit 0 

group=physics

#ANA_DIR=`pwd`
#echo Current dir: $ANA_DIR
#echo Works dir: $WORK_DIR
#echo Works dir: $3/$1
#------ana_dir----replace path with what your analysis dir---------#
#1.signalMC
#2.signalShapeMC
#3.inclusiveMC
MACRO_DIR=/besfs5/users/zengsh/7.0.6/LcTag/HOME
#MACRO_DIR=/besfs5/users/w2530205166/MC
#ANA_DIR=/besfs5/users/zengsh/7.0.6/LcTag
ANA_DIR=/publicfs/ucas/user/qinjj/Public/ForSh
#ANA_DIR=/besfs5/users/w2530205166/MC/PKPI
#ANA_DIR=/scratchfs/bes/zengsh/7.0.6/LcTag
#MACRO_DIR=/scratchfs/bes/zengsh/7.0.6/LcTag/HOME
echo main dir: $ANA_DIR
echo Works dir: $ANA_DIR/signalMC/$1

#DST_DIR=${ANA_DIR}/dst
#RTRAW_DIR=${ANA_DIR}/rtraw
#DEC_DIR=${ANA_DIR}/dec
#RTRAW_DIR=` echo ${RTRAW_DIR} |sed 's/\/$//'`
#JOB_DIR=${ANA_DIR}/joblist

DST_DIR=$ANA_DIR/signalMC/$3/$1/dst
RTRAW_DIR=$ANA_DIR/signalMC/$3/$1/rtraw
DEC_DIR=$MACRO_DIR/dec
#RTRAW_DIR=` echo ${RTRAW_DIR} |sed 's/\/$//'`
#JOB_DIR=$3/$1/joblist
JOB_DIR=$ANA_DIR/signalMC/joblist
NAME=${name}$3
mkdir -p  ${RTRAW_DIR} ${JOB_DIR} ${DST_DIR} 
cd  ${JOB_DIR}
#rm -f *txt list* subjob *condor 
i_num=0
#i_num=70
while [ $i_num -lt $num ]
do 
  fake_num=`printf "%04d\n" ${i_num}`
  SIM_JOB_FILE=${name}$3_sim_${fake_num}.txt
  echo $SIM_JOB_FILE
SEED1=$RANDOM
SEED2=$RANDOM
SEED=${SEED1}${SEED2}

  cat $MACRO_DIR/sim_ini/run_template_head.txt |sed "s#ECMS#$4#g" |sed "s#BEAMS#$5#g" |sed "s#RUN1#$6#g" |sed "s#RUN2#$7#g" |sed "s#RANDOM#${SEED}#g" | sed "s#DEC#${DEC_DIR}/${name}#g" >${SIM_JOB_FILE}
	cat $MACRO_DIR/sim_ini/run_template_tail.txt | sed "s#NAME#${RTRAW_DIR}/${NAME}_sim_${fake_num}#g" | sed "s#LIPR#$date#g" >> ${SIM_JOB_FILE}
	echo boss.condor ${SIM_JOB_FILE}>>list_sim

  REC_JOB_FILE=${NAME}_rec_${fake_num}.txt
  echo $REC_JOB_FILE
SEED1=$RANDOM
SEED2=$RANDOM
SEED=${SEED1}${SEED2}
  cat $MACRO_DIR/rec_ini/run_template_head.txt | sed "s#RANDOM#${SEED}#g" >${REC_JOB_FILE}
	cat $MACRO_DIR/rec_ini/run_template_tail.txt |sed "s#NAMEA#${RTRAW_DIR}/${NAME}_sim_${fake_num}#g"| sed "s#NAMEB#${DST_DIR}/${NAME}_rec_${fake_num}#g" | sed "s#LIPR#$date#g" >> ${REC_JOB_FILE}
	echo boss.condor ${REC_JOB_FILE}>>list_rec

  i_num=`expr ${i_num} + 1`
  date=`expr ${date} + 1`

done

JobExe=${NAME}_sim_rec.condor
CmdJobId="grep GlobalJobId \$_CONDOR_JOB_AD | cut -d'#' -f2"
CmdJobSlot="grep RemoteHost \$_CONDOR_JOB_AD"

echo "#!/bin/tcsh -f" > ${JobExe}
echo "cd ${JOB_DIR}" >> ${JobExe}

echo "set procid=\$1" >> ${JobExe} 
echo "set sub_name_number=\`expr \$procid\`" >> ${JobExe}
echo "set sub_name=\`printf \"%04d\n\" \$sub_name_number\`" >> ${JobExe}
echo "set JobID=\$_CONDOR_IHEP_JOB_ID" >> ${JobExe}
echo "set JobHOST=\$_CONDOR_IHEP_REMOTE_HOST" >> ${JobExe}
echo "#set JobTIME=\$_CONDOR_IHEP_SUBMISSION_TIME" >> ${JobExe}

echo "echo \"Job \${JobID} on RemoteHost = \${JobHOST}\" > ${NAME}_sim_\${sub_name}.txt.bosslog"  >> ${JobExe}
echo "((time boss.exe ${NAME}_sim_\${sub_name}.txt) >> ${NAME}_sim_\${sub_name}.txt.bosslog) >& ${NAME}_sim_\${sub_name}.txt.bosserr" >> ${JobExe}
echo "sleep 3" >> ${JobExe}

echo "echo \"Job \${JobID} on RemoteHost = \${JobHOST}\" > ${NAME}_rec_\${sub_name}.txt.bosslog"  >> ${JobExe}
echo "((time boss.exe ${NAME}_rec_\${sub_name}.txt) >> ${NAME}_rec_\${sub_name}.txt.bosslog) >& ${NAME}_rec_\${sub_name}.txt.bosserr" >> ${JobExe}
echo "sleep 3" >> ${JobExe}
#echo "rm -f ${JobExe}" >> ${JobExe}

chmod u+x ${JobExe}

echo "hep_sub -g ${group} -o /dev/null -e /dev/null ${JobExe} -argu \"%{ProcId}\" -n $num" >> subjob
#echo "hep_sub -os SL6 -wt mid -g ${group} -o /dev/null -e /dev/null ${JobExe} -argu \"%{ProcId}\" -n $num" > subjob
#echo "hep_sub -os SL6 -g ${group} -o /dev/null -e /dev/null ${JobExe} -argu \"%{ProcId}\" -n $num" > subjob

echo !!!!!DONE!!!!! 
