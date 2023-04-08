# Script for automatically computing average derivations on all executions results

# Retrieve best known values
best.known <- read.table("assets/solutions/Best-known Values", sep=" ", header=TRUE)

# Retrieve the tests data
files <- list.files(path="out", full.names=TRUE, recursive=TRUE)

# For each test file, compute
for (algo in files) {
  # Get algorithm results
  score.instances <- read.table(algo, sep=" ", header=TRUE)

  # Average the values for solution score and execution time w.r.t the instance
  mean.result <- aggregate(cbind(Score, Time) ~ Instance + Size, data=score.instances, FUN=mean)

  # Compute the relative percentage deviation
  instance.cost <- 100 * (mean.result$Score - best.known$Value) / best.known$Value

  # Store the results of each instance (relative percentage deviation + execution time)
  result <- data.frame("Instance"=best.known$Instance, "Size"=mean.result$Size, "Deviation"=instance.cost, "Time"=mean.result$Time)

  # Create output files for the results (separated per algorithm)
  file.create(paste0("src/statistics/stats/algo/", basename(algo)))
  write.table(result, file=paste0("src/statistics/stats/algo/", basename(algo)), row.names=FALSE, quote=FALSE)
}

# Get all the results from previous steps
results <- list.files(path="src/statistics/stats/algo", full.names=TRUE, recursive=TRUE)

# Store algorithms name (same order as results files)
algos <- vector(length=length(results))
for (i in seq_along(results)) {
  algos[i] <- basename(results[i])
}

# Prepare for computation of the tests
t_tests <- matrix(nrow=length(results), nco=length(results), dimnames=list(algos, algos))
wilcox_tests <- matrix(nrow=length(results), nco=length(results), dimnames=list(algos, algos))

# Compute test results for each pair of algorithms
for (i in seq_along(results)) {
  for (j in seq_along(results)) {

    # Get the selected algorithms results
    a.cost <- read.table(results[i], sep=" ", header=TRUE)$Deviation
    b.cost <- read.table(results[j], sep=" ", header=TRUE)$Deviation

    # Paired t-test
    t_tests[i, j] <- t.test(a.cost, b.cost, paired=TRUE)$p.value

    # Wilcoxon signed-rank test
    wilcox_tests[i, j] <- wilcox.test(a.cost, b.cost, paired=TRUE)$p.value
  }
}

# Store the results of the statistical tests in a file
write.table(t_tests, file="src/statistics/results/algo/t_test", row.names=FALSE, quote=FALSE)
write.table(wilcox_tests, file="src/statistics/results/algo/wilcox_test", row.names=FALSE, quote=FALSE)
