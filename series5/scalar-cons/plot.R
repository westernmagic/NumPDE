library(magrittr)
library(tibble)
library(dplyr)
library(tidyr)
library(stringr)
library(ggplot2)

read_data <- function(filename) {
	read.table(filename) %>%
		t %>%
		as_tibble %>%
		.$V1
}

read_solution <- function(path, exact_solution) {
		tibble(
			Godunov      = read_data(paste0(path, "_G.txt")),
			LaxFriedrich = read_data(paste0(path, "_LF.txt"))
		) %>%
		mutate(
			x     = seq(-2, 2, along.with = Godunov),
			Exact = exact_solution(x)
		)
}

burgers1_exact <- function(x, t = 0.8) {
	if_else(x < 0.5 * t, 1, 0)
}

burgers2_exact <- function(x, t = 0.8) {
	if_else(x < -t, 0, -2)
}

burgers3_exact <- function(x, t = 0.8) {
	case_when(
		x < 0 ~ 0,
		x < t ~ x / t,
		TRUE ~ 1
	)
}

burgers4_exact <- function(x, t = 0.8) {
	case_when(
		x <= 0 ~ 0,
		(x <= t & t <= 2) | (x < sqrt(2 * t) & t > 2) ~ x / t,
		(t <= 2 & t < x)  & (x < (1 + t / 2)) ~ 1,
		TRUE ~ 0
	)
}

bind_rows(
	read_solution("series5/build/uBi", burgers1_exact)   %>% mutate(InitialConditions = "Burgers' 1"),
	read_solution("series5/build/uBii", burgers2_exact)  %>% mutate(InitialConditions = "Burgers' 2"),
	read_solution("series5/build/uBiii", burgers3_exact) %>% mutate(InitialConditions = "Burgers' 3"),
	read_solution("series5/build/uBiv", burgers4_exact)  %>% mutate(InitialConditions = "Burgers' 4"),
	read_solution("series5/build/uBL", . %>% {NA})       %>% mutate(InitialConditions = "Buckley-Leverett")
) %>%
	gather(Type, u, -x, -InitialConditions) %>%
	filter(!is.na(u)) %>% {
		ggplot(., aes(x = x, y = u, color = Type)) +
			facet_wrap(~InitialConditions, scales = "free") +
			geom_line(data = filter(., Type == "Exact")) +
			geom_step(data = filter(., Type != "Exact"))
	}

error_data <- lapply(1:4, function(i) {
	path <- "series5/build/Burgers"
	tibble(
		InitialConditions = i,
		Resolutions       = read_data(paste0(path, i, "_resolutions.txt")),
		L1_Godunov        = read_data(paste0(path, i, "_L1errors_Godunov.txt")),
		Linf_Godunov      = read_data(paste0(path, i, "_Linferrors_Godunov.txt")),
		L1_LaxFriedrich   = read_data(paste0(path, i, "_L1errors_LF.txt")),
		Linf_LaxFriedrich = read_data(paste0(path, i, "_Linferrors_LF.txt"))
	)
}) %>%
	bind_rows %>%
	gather(Type, Error, -InitialConditions, -Resolutions) %>%
	mutate(
		Error_Type = str_split(Type, "_", simplify = TRUE)[,1],
		Method     = str_split(Type, "_", simplify = TRUE)[,2]
	) %>%
	select(-Type)

error_orders <- error_data %>%
	group_by(InitialConditions, Method, Error_Type) %>%
	do(lm = lm(log(Error) ~ log(Resolutions), data = .)) %>%
	mutate(Order = summary(lm)$coeff[2]) %>%
	select(-lm)

error_data %>%
	ggplot(aes(x = Resolutions, y = Error, color = Error_Type)) +
	coord_trans("log10", "log10") +
	facet_grid(InitialConditions ~ Method) +
	geom_line() +
	geom_text(data = error_orders, aes(label = Order %>% round(2) %>% format(2), vjust = if_else(Error_Type == "Linf", -1, 0)), x = 0, y = 0, hjust = 0)


