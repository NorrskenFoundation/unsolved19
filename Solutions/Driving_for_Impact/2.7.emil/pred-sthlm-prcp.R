jsons <- dir("data") %>%
  purrr::map(~ file.path("data", .) %>% jsonlite::fromJSON())

gstpd <- jsons %>% # geo spatial temporal prec data
  purrr::map(~ list(
    time = as.POSIXct(.$time, origin = "1970-01-01"),
    values = .$points$properties$value,
    cords = .$points$geometry$coordinates
  )) %>%
  purrr::map_if(~ is.null(.$values), ~ purrr::update_list(., values = 0, cords = list(c(NA, NA)))) %>%
  purrr::map(~ purrr::update_list(., cords = .$cords %>% purrr::map(~ data.frame(lon = .[1], lat = .[2])) %>% purrr::reduce(rbind))) %>%
  purrr::map(~ data.frame(timestamp = .$time, val = .$values, lon = .$cords$lon, lat = .$cords$lat)) %>%
  purrr::reduce(rbind) %>%
  dplyr::arrange(timestamp, lon, lat)

avail_coords <- gstpd %>%
  dplyr::group_by(lon, lat) %>%
  dplyr::summarize(n = dplyr::n()) %>%
  dplyr::ungroup() %>%
  dplyr::select(lon, lat) %>%
  na.omit() %>%
  dplyr::arrange(lon, lat)
dims <- avail_coords %>%
  tidyr::crossing(data.frame(timestamp = gstpd$timestamp), by = NULL) %>%
  dplyr::arrange(timestamp, lon, lat)

cgstpd <- dims %>% # complete gstpd
  dplyr::left_join(gstpd) %>%
  dplyr::mutate(val = ifelse(is.na(val), 0, val)) %>%
  dplyr::arrange(timestamp, lon, lat)

#### SMARIMA
library(starma)
library(spdep)

max_dist <- max(
  avail_coords$lon %>% unique() %>% sort() %>% diff() %>% na.omit() %>% abs() %>% max(),
  avail_coords$lat %>% unique() %>% sort() %>% diff() %>% na.omit() %>% abs() %>% max()
)
knb <- avail_coords %>%
  na.omit() %>%
  as.matrix() %>%
  spdep::dnearneigh(0, max_dist)
knb <- spdep::nblag(knb, 4)
klist <- list(
  order0 = diag(nrow(avail_coords)),
  order1 = spdep::nb2mat(knb[[1]], zero.policy = TRUE),
  order2 = spdep::nb2mat(knb[[2]], zero.policy = TRUE),
  order3 = spdep::nb2mat(knb[[3]], zero.policy = TRUE),
  order4 = spdep::nb2mat(knb[[4]], zero.policy = TRUE)
)

star <- cgstpd %>%
  dplyr::mutate(pos = paste0("N", lat, "/E", lon)) %>%
  dplyr::select(pos, timestamp, val) %>%
  tidyr::pivot_wider(names_from = pos, values_from = val) %>%
  dplyr::select(-timestamp) %>%
  as.matrix()

starc <- starma::stcenter(star) # Center and scale the dataset
starma::stacf(starc, klist)

# Identify the process
starma::stacf(starc, klist)
starma::stpacf(starc, klist)
# Estimate the process
ar <- matrix(c(1, 1, 1, 0), 2, 2)
ma <- matrix(c(0, 1), 1, 2)
model <- starma::starma(starc, klist, ar, ma)
summary(model)
# Diagnose the process
starma::stcor.test(model$residuals, klist, fitdf = 4)
starma::stacf(model$residuals, klist)
starma::stpacf(model$residuals, klist)

# jsons %>%
#   purrr::map(~ as.POSIXct(.$time, origin = "1970-01-01")) %>%
#   unlist() %>%
#   as.POSIXct(origin = "1970-01-01") %>%
#   sort()

# avail_coords %>%
#   ggplot2::ggplot(ggplot2::aes(x = lon, y = lat)) +
#   ggplot2::geom_point()
