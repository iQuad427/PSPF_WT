# PLOT THE QRTDs

tabu.files <- list.files("src/statistics/implementation-2/results/rtd", pattern=".*_tabu.*", full.names=TRUE, recursive=FALSE)
gen.files <- list.files("src/statistics/implementation-2/results/rtd", pattern=".*_memetic.*", full.names=TRUE, recursive=FALSE)

colors <- c("red", "grey", "green", "black")
references <- c(0.6, 0.65, 0.7, 0.75, 0.8)

for (instance in 51:55) {
  pattern <- paste0('.*', instance, '.*')
  files <- tabu.files[grep(pattern, tabu.files)]

  data <- read.table(files[length(files)], sep=" ", header=TRUE)
  plot(data$Time, data$Probability, main = paste0("QRTD of instance DD_Ta0", instance, " Tabu"),
       log = "x", type = "l", col = "blue", lwd = 2, xlab = "Time [sec]", ylab = "Probability")

  for (i in rev(seq_along(files))) {
    data <- read.table(files[i], sep=" ", header=TRUE)
    lines(data$Time, data$Probability, col = colors[i], type = "l", lwd = 2)
  }

  # add a legend
  legend("topleft", legend = rev(references), col = c("blue", rev(colors)), lty = 1, lwd = 2)

}

# for (instance in 51:55) {
#   pattern <- paste0('.*', instance, '.*')
#   files <- gen.files[grep(pattern, gen.files)]
#
#   print(files[length(files)])
#
#   data <- read.table(files[length(files)], sep=" ", header=TRUE)
#   plot(data$Time, data$Probability, main = paste0("QRTD of instance DD_Ta0", instance, " Memetic"),
#        log = "x", type = "l", col = "blue", lwd = 2, xlab = "Time [sec]", ylab = "Probability")
#
#   for (i in rev(seq_along(files))) {
#     data <- read.table(files[i], sep=" ", header=TRUE)
#     lines(data$Time, data$Probability, col = colors[i], type = "l", lwd = 2)
#   }
#
#   # add a legend
#   legend("topleft", legend = rev(references), col = c("blue", rev(colors)), lty = 1, lwd = 2)
# }
