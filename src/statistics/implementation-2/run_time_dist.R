rm(list=ls())

# DEVIATION FROM BEST-KNOWN SOLUTION

# Retrieve best known values
best.known <- read.table("assets/solutions/Best-known Values", sep=" ", header=TRUE)

# Retrive algorithm result files
tabu.files <- list.files("out/rtd/tabu", pattern=".*_.*", full.names=TRUE, recursive=FALSE)
gen.files <- list.files("out/rtd/memetic", pattern=".*_.*", full.names=TRUE, recursive=FALSE)

# for (instance in tabu.files) {
#   # Get algorithm results
#   score.instances <- read.table(instance[1], sep=" ", header=FALSE)
#   colnames(score.instances) <- c("Time", "Score")
#
#   # Compute the relative percentage deviation
#   name <- substr(basename(instance), start = 1, stop = 8)
#   best.score <- best.known$Value[which(best.known$Instance == name)]
#   instance.cost <- 100 * (score.instances$Score - best.score) / best.score
#
#   # Store the results of each instance (relative percentage deviation + execution time)
#   result <- data.frame("Time"=score.instances$Time, "Deviation"=instance.cost)
#
#   # Create output files for the results (separated per algorithm)
#   file.create(paste0("src/statistics/implementation-2/stats/rtd/tabu/", basename(instance)))
#   write.table(result, file=paste0("src/statistics/implementation-2/stats/rtd/tabu/", basename(instance)), row.names=FALSE, quote=FALSE)
# }
#
# for (instance in gen.files) {
#   # Get algorithm results
#   score.instances <- read.table(instance[1], sep=" ", header=FALSE)
#   colnames(score.instances) <- c("Time", "Score")
#
#   # Compute the relative percentage deviation
#   name <- substr(basename(instance), start = 1, stop = 8)
#   best.score <- best.known$Value[which(best.known$Instance == name)]
#   instance.cost <- 100 * (score.instances$Score - best.score) / best.score
#
#   # Store the results of each instance (relative percentage deviation + execution time)
#   result <- data.frame("Time"=score.instances$Time, "Deviation"=instance.cost)
#
#   # Create output files for the results (separated per algorithm)
#   file.create(paste0("src/statistics/implementation-2/stats/rtd/memetic/", basename(instance)))
#   write.table(result, file=paste0("src/statistics/implementation-2/stats/rtd/memetic/", basename(instance)), row.names=FALSE, quote=FALSE)
# }

# COMPUTE RUN-TIME DISTRIBUTION

# tabu.files <- list.files("src/statistics/implementation-2/stats/rtd/tabu", pattern=".*_.*", full.names=TRUE, recursive=FALSE)
# gen.files <- list.files("src/statistics/implementation-2/stats/rtd/memetic", pattern=".*_.*", full.names=TRUE, recursive=FALSE)

references <- c(0.60, 0.65, 0.70, 0.75, 0.80)

for (instance in 51:55) {
  print(paste("Instance :", instance))

  pattern <- paste0('.*', instance, '.*')
  files <- tabu.files[grep(pattern, tabu.files)]

  timestamps <- seq(from = 0, to = 10, by = 0.0001)

  name <- paste0("DD_Ta0", instance)
  best.score <- best.known$Value[which(best.known$Instance == name)]
  print(best.score)

  for (alpha in references) {
    print(paste("alpha :", alpha))
    counts <- numeric(length(timestamps))
    reference <- alpha * best.score

    print("file being processed :")
    for (i in seq_along(files)) {
      cat(i, "")
      data <- read.table(files[i], sep=" ", header=FALSE)
      colnames(data) <- c("Time", "Score")

      for (t in seq_along(timestamps)) {
        index <- which(data$Time <= timestamps[t])

        if (length(index) != 0) {
          sample <- data[index[length(index)],]
          if (sample$Score < reference) {
            counts[t] <- counts[t] + 1
          }
        }
      }
    }
    cat("\n")

    proba <- counts / 25
    results <- data.frame("Time"=timestamps, "Probability"=proba)

    file.name <- paste0("src/statistics/implementation-2/results/rtd/DD_Ta0", instance, "_tabu_", alpha)
    file.create(file.name)
    write.table(results, file=file.name, row.names=FALSE, quote=FALSE)
  }
}

for (instance in 51:55) {
  print(paste("Instance :", instance))

  pattern <- paste0('.*', instance, '.*')
  files <- gen.files[grep(pattern, gen.files)]

  timestamps <- seq(from = 0, to = 60, by = 0.01)

  name <- paste0("DD_Ta0", instance)
  best.score <- best.known$Value[which(best.known$Instance == name)]
  print(best.score)

  for (alpha in references) {
    print(paste("alpha :", alpha))
    counts <- numeric(length(timestamps))
    reference <- alpha * best.score

    print("file being processed :")
    for (i in seq_along(files)) {
      cat(i, "")
      data <- read.table(files[i], sep=" ", header=FALSE)
      colnames(data) <- c("Time", "Score")

      for (t in seq_along(timestamps)) {
        index <- which(data$Time <= timestamps[t])

        if (length(index) != 0) {
          sample <- data[index[length(index)],]
          if (sample$Score < reference) {
            counts[t] <- counts[t] + 1
          }
        }
      }
    }
    cat("\n")

    proba <- counts / 25
    results <- data.frame("Time"=timestamps, "Probability"=proba)

    file.name <- paste0("src/statistics/implementation-2/results/rtd/DD_Ta0", instance, "_memetic_", alpha)
    file.create(file.name)
    write.table(results, file=file.name, row.names=FALSE, quote=FALSE)
  }
}