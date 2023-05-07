rm(list=ls())

# Retrieve best known values
best.known <- read.table("assets/solutions/Best-known Values", sep=" ", header=TRUE)

# Retrieve the data for comparison of the best tabu tenure
files <- list.files(path="out", pattern="tabu.*max_time-10", full.names=TRUE, recursive=TRUE)

for (algo in files) {
  # Get algorithm results
  score.instances <- read.table(algo, sep=" ", header=TRUE)

  if (NROW(score.instances) == 20)
    # Average the values for solution score and execution time w.r.t the instance
    mean.result <- aggregate(cbind(Score, Time) ~ Instance + Size, data=score.instances, FUN=mean)

    # Compute the relative percentage deviation
    instance.cost <- 100 * (mean.result$Score - best.known$Value) / best.known$Value

    # Store the results of each instance (relative percentage deviation + execution time)
    result <- data.frame("Instance"=best.known$Instance, "Size"=mean.result$Size, "Deviation"=instance.cost, "Time"=mean.result$Time)

    # Create output files for the results (separated per algorithm)
    file.create(paste0("src/statistics/implementation-2/stats/tabu/", basename(algo)))
    write.table(result, file=paste0("src/statistics/implementation-2/stats/tabu/", basename(algo)), row.names=FALSE, quote=FALSE)
}

rm(list=ls())

tenures <- c(0, 3, 5, 7, 10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120, 130, 140, 150, 200)

deviation_50 <- NULL
deviation_100 <- NULL
deviation_tot <- NULL

for (tenure in tenures) {
  tabu.file <- list.files(
    path="src/statistics/implementation-2/stats/tabu",
    pattern=paste0("tabu.*-", tenure,"-.*max_time-10"), full.names=TRUE, recursive=TRUE
  )

  tabu.dev <- read.table(tabu.file[1], sep=" ", header=TRUE)

  mean.result <- aggregate(Deviation ~ Size, data=tabu.dev, FUN=mean)

  deviation_50 <- c(deviation_50, mean.result[1,2])
  deviation_100 <- c(deviation_100, mean.result[2,2])
  deviation_tot <- c(deviation_tot, (mean.result[1,2] + mean.result[2,2])/2)
}

result <- data.frame(
  "Tenure"=tenures,
  "Deviation-50"=deviation_50,
  "Deviation-100"=deviation_100,
  "Deviation-total"=deviation_tot
)

write.table(result, file="src/statistics/implementation-2/results/tabu_tenure", row.names=FALSE, quote=FALSE)

cat("\nRESULTS (best tenure)\n")
cat("Best Tenure, instance of size 50  :", tenures[which.min(deviation_50)], "\n")
cat("Best Tenure, instance of size 100 :", tenures[which.min(deviation_100)], "\n")
cat("Best Tenure, overall              :", tenures[which.min(deviation_tot)], "\n")