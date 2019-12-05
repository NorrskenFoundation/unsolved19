package com.netlight.Norrsken.clients;

import com.fasterxml.jackson.databind.ObjectMapper;
import com.google.common.cache.Cache;
import com.netlight.Norrsken.clients.domain.EricssonWeatherData;

import javax.ws.rs.client.ClientBuilder;
import javax.ws.rs.core.HttpHeaders;
import javax.ws.rs.core.Response;
import java.io.IOException;
import java.io.UncheckedIOException;
import java.time.OffsetDateTime;
import java.time.format.DateTimeFormatter;
import java.util.Optional;
import java.util.concurrent.ExecutionException;

public class EricssonWeatherClient {
  String url;
  String path;
  DateTimeFormatter dateTimeFormatter;
  Cache<String, Optional<EricssonWeatherData>> cache;

  private ObjectMapper objectMapper;

  public EricssonWeatherClient(
      String url,
      String path,
      ObjectMapper objectMapper,
      Cache<String, Optional<EricssonWeatherData>> cache) {
    this.url = url;
    this.path = path;
    this.objectMapper = objectMapper;
    this.cache = cache;
    dateTimeFormatter = DateTimeFormatter.ofPattern("YYYYMMddHHmm");
  }

  public Optional<EricssonWeatherData> getWeatherData(OffsetDateTime time, String token) {
    String timeString = dateTimeFormatter.format(time);
    try {
      return cache.get(
          timeString,
          () -> {
            String target = path + "/" + timeString;
            Response response =
                ClientBuilder.newClient()
                    .target(url)
                    .path(target)
                    .queryParam("location", "stockholm")
                    .request()
                    .header(HttpHeaders.AUTHORIZATION, String.format("Bearer %s", token))
                    .get();
            if (response.getStatus() == 200) {
              String responseString = response.readEntity(String.class);
              System.out.println(responseString);
              try {
                return Optional.of(
                    objectMapper.readValue(responseString, EricssonWeatherData.class));
              } catch (IOException e) {
                throw new UncheckedIOException("Failed to parse json", e);
              }
            }
            return Optional.empty();
          });
    } catch (ExecutionException e) {
      e.printStackTrace();
      return null;
    }
  }
}
