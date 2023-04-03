# Retrieve best known values
best.known <- read.table("assets/solutions/Best-known Values", sep=" ", header=TRUE)

# Retrieve the tests data
files.rand <- list.files(path="out", pattern="ii.*rnd.*", full.names=TRUE, recursive=TRUE)
files.srz <- list.files(path="out", pattern="ii.*srz.*", full.names=TRUE, recursive=TRUE)

# For each algorithm having random initialisation
rand.result <- data.frame(matrix(nrow=0, ncol=3, dimnames=list(NULL, c("Size", "Deviation", "Time"))))
srz.result <- data.frame(matrix(nrow=0, ncol=3, dimnames=list(NULL, c("Size", "Deviation", "Time"))))

for (algo in files.rand) {
  # Get algorithm results
  score.instances <- read.table(algo, sep=" ", header=TRUE)

  # Average the values for solution score and execution time w.r.t the instance
  mean.result <- aggregate(cbind(Score, Time) ~ Instance + Size, data=score.instances, FUN=mean)

  # Compute the relative percentage deviation
  instance.cost <- 100 * (mean.result$Score - best.known$Value) / best.known$Value

  # Store the results of each instance (relative percentage deviation + execution time)
  result <- data.frame("Size"=mean.result$Size, "Deviation"=instance.cost, "Time"=mean.result$Time)
  rand.result <- rbind(rand.result, result)

  # Create output files for the results (separated per algorithm)
  write.table(result, file=paste0("src/statistics/stats/init/random/", basename(algo)), row.names=FALSE, quote=FALSE)
}

# Average the values for solution derivation and execution time w.r.t to the size of the instance
rand.result <- aggregate(cbind(Deviation, Time) ~ Size, data=rand.result, FUN=mean)

# Create output files for the results
write.table(rand.result, file=paste0("src/statistics/results/init/", "result_random"), row.names=FALSE, quote=FALSE)

for (algo in files.srz) {
  # Get algorithm results
  score.instances <- read.table(algo, sep=" ", header=TRUE)

  # Average the values for solution score and execution time w.r.t the instance
  mean.result <- aggregate(cbind(Score, Time) ~ Instance + Size, data=score.instances, FUN=mean)

  # Compute the relative percentage deviation
  instance.cost <- 100 * (mean.result$Score - best.known$Value) / best.known$Value

  # Store the results of each instance (relative percentage deviation + execution time)
  result <- data.frame("Size"=mean.result$Size, "Deviation"=instance.cost, "Time"=mean.result$Time)
  srz.result <- rbind(srz.result, result)

  # Create output files for the results (separated per algorithm)
  write.table(result, file=paste0("src/statistics/stats/init/simple_rz/", basename(algo)), row.names=FALSE, quote=FALSE)
}

# Average the values for solution derivation and execution time w.r.t to the size of the instance
srz.result <- aggregate(cbind(Deviation, Time) ~ Size, data=srz.result, FUN=mean)

# Create output files for the results
write.table(srz.result, file=paste0("src/statistics/results/init/", "result_srz"), row.names=FALSE, quote=FALSE)