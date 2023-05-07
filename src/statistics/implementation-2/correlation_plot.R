rm(list=ls())

# DEVIATION FROM BEST-KNOWN SOLUTION

# Retrieve best known values
best.known <- read.table("assets/solutions/Best-known Values", sep=" ", header=TRUE)

# Retrive algorithm result files
tabu.files <- list.files("out", pattern="tabu.*tenure-100.*max_time-120", full.names=TRUE, recursive=TRUE)
gen.files <- list.files("out", pattern="gen.*pop_size-100-mut_rate-0.7.*-max_time-120", full.names=TRUE, recursive=TRUE)

for (algo in c(tabu.files, gen.files)) {
  # print(algo)
  # Get algorithm results
  score.instances <- read.table(algo[1], sep=" ", header=TRUE)

  # Average the values for solution score and execution time w.r.t the instance
  mean.result <- aggregate(cbind(Score, Time) ~ Instance + Size, data=score.instances, FUN=mean)

  # Compute the relative percentage deviation
  instance.cost <- 100 * (mean.result$Score - best.known$Value) / best.known$Value

  # Store the results of each instance (relative percentage deviation + execution time)
  result <- data.frame("Instance"=best.known$Instance, "Size"=mean.result$Size, "Deviation"=instance.cost, "Time"=mean.result$Time)

  # Create output files for the results (separated per algorithm)
  file.create(paste0("src/statistics/implementation-2/stats/comparison/", basename(algo)))
  write.table(result, file=paste0("src/statistics/implementation-2/stats/comparison/", basename(algo)), row.names=FALSE, quote=FALSE)
}

# STATISTICS ON THE RESULTS

tabu <- read.table("src/statistics/implementation-2/stats/comparison/tabu-rnd-ex-tenure-100-max_time-120", header=TRUE)
gen <- read.table("src/statistics/implementation-2/stats/comparison/gen-ex-pop_size-100-mut_rate-0.700000-max_time-120", header=TRUE)

result <- data.frame(
  "instances"=tabu$Instance,
  "instances.size"=tabu$Size,
  "deviation.tabu"=tabu$Deviation,
  "deviation.gen"=gen$Deviation
)

p.value <- wilcox.test(tabu$Deviation, gen$Deviation, paired=TRUE)$p.value
p.value

tabu.mean <- aggregate(Deviation ~ Size, data=tabu, FUN=mean)
gen.mean <- aggregate(Deviation ~ Size, data=gen, FUN=mean)

# CORRELATION PLOT

tabu.50 <- tabu[tabu$Size==50,]$Deviation
tabu.100 <- tabu[tabu$Size==100,]$Deviation

gen.50 <- gen[gen$Size==50,]$Deviation
gen.100 <- gen[gen$Size==100,]$Deviation

# Plot the result
plot(tabu.50, gen.50, pch=16, col="blue",
     xlab="Tabu Search", ylab = "Memetic Algorithm",
     main = "Correlation Plot of Deviation (size = 50)"
)
fit.50 <- lm(gen.50 ~ tabu.50, data=data.frame(cbind(tabu.50, gen.50)))
abline(fit.50, col = "black")

plot(tabu.100, gen.100, pch=16, col="red",
     xlab="Tabu Search", ylab = "Memetic Algorithm",
     main = "Correlation Plot of Deviation (size = 100)"
)
fit.100 <- lm(gen.100 ~ tabu.100, data=data.frame(cbind(tabu.100, gen.100)))
abline(fit.100, col = "black")

# BOTH ON SAME GRAPH

plot(tabu.50, gen.50, pch=16, col="blue",
     xlab="Tabu Search", ylab = "Memetic Algorithm",
     main = "Correlation Plot of Deviation",
     xlim = c(max(tabu.50, tabu.100), min(tabu.50, tabu.100)),
     ylim = c(max(gen.50, gen.100), min(gen.50, gen.100))
)

points(tabu.100, gen.100, pch=16, col="red")

data.frame(cbind(tabu$Deviation, gen$Deviation))
fit <- lm(X2 ~ X1, data=data.frame(cbind(tabu$Deviation, gen$Deviation)))
abline(fit, col = "green")
abline(fit.50, col = "blue")
abline(fit.100, col = "red")

# add a legend to the plot
legend("topright", legend = c("Instance of size 50","Instance of size 100","Both isntances"), col = c("blue","red", "green"), pch=16)