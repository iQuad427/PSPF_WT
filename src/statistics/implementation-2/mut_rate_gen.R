rm(list=ls())

# Retrieve best known values
best.known <- read.table("assets/solutions/Best-known Values", sep=" ", header=TRUE)[1:10,]

# Retrieve the data for comparison of the best tabu tenure
files <- list.files(path="out/gen/compare_mut_rate", full.names=TRUE, recursive=TRUE)

for (algo in files) {
  # Get algorithm results
  score.instances <- read.table(algo, sep=" ", header=TRUE)

  if (NROW(score.instances) == 10)
    # Average the values for solution score and execution time w.r.t the instance
    mean.result <- aggregate(cbind(Score, Time) ~ Instance + Size, data=score.instances, FUN=mean)

    # Compute the relative percentage deviation
    instance.cost <- 100 * (mean.result$Score - best.known$Value) / best.known$Value

    # Store the results of each instance (relative percentage deviation + execution time)
    result <- data.frame("Instance"=best.known$Instance, "Size"=mean.result$Size, "Deviation"=instance.cost, "Time"=mean.result$Time)

    # Create output files for the results (separated per algorithm)
    file.create(paste0("src/statistics/implementation-2/stats/gen/mut_rate/", basename(algo)))
    write.table(result, file=paste0("src/statistics/implementation-2/stats/gen/mut_rate/", basename(algo)), row.names=FALSE, quote=FALSE)
}

rm(list=ls())

mutations <- c(0.0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0)

deviation_50 <- NULL
for (mutation in mutations) {
  gen.file <- list.files(
    path="src/statistics/implementation-2/stats/gen/mut_rate",
    pattern=paste0("gen.*-", mutation,".*max_time-30"), full.names=TRUE, recursive=TRUE
  )

  gen.dev <- read.table(gen.file[1], sep=" ", header=TRUE)

  mean.result <- aggregate(Deviation ~ Size, data=gen.dev, FUN=mean)

  deviation_50 <- c(deviation_50, mean.result[1,2])
}

result <- data.frame(
  "Mutation-Rate"=mutations,
  "Deviation-50"=deviation_50
)

write.table(result, file="src/statistics/implementation-2/results/gen_mut_rate", row.names=FALSE, quote=FALSE)

cat("\nRESULTS (best mutation rate)\n")
cat("Best Tenure, instance of size 50  :", mutations[which.min(deviation_50)], "\n")