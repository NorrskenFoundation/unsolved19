package com.netlight.Norrsken;

import com.fasterxml.jackson.databind.DeserializationFeature;
import com.fasterxml.jackson.databind.ObjectMapper;
import com.fasterxml.jackson.databind.SerializationFeature;
import com.fasterxml.jackson.datatype.jsr310.JavaTimeModule;
import com.google.common.cache.Cache;
import com.google.common.cache.CacheBuilder;
import com.netlight.Norrsken.clients.EricssonWeatherClient;
import com.netlight.Norrsken.clients.domain.EricssonWeatherData;
import org.springframework.context.annotation.Bean;

import java.time.Duration;
import java.util.Optional;

@org.springframework.context.annotation.Configuration
public class Configuration {
  public static final String TOKEN =
      "eyJ4NXQiOiJOVEF4Wm1NeE5ETXlaRGczTVRVMVpHTTBNekV6T0RKaFpXSTRORE5sWkRVMU9HRmtOakZpTVEiLCJraWQiOiJOVEF4Wm1NeE5ETXlaRGczTVRVMVpHTTBNekV6T0RKaFpXSTRORE5sWkRVMU9HRmtOakZpTVEiLCJhbGciOiJSUzI1NiJ9.eyJzdWIiOiJhbGV4YW5kZXIubmFqYWZpQG5ldGxpZ2h0LmNvbUBjYXJib24uc3VwZXIiLCJhdWQiOiJQcnFmNTk5NHYyd1Rva3VoelNnR0JrVDdYdm9hIiwiYXpwIjoiUHJxZjU5OTR2MndUb2t1aHpTZ0dCa1Q3WHZvYSIsInNjb3BlIjoiYXBpbTpzdWJzY3JpYmUiLCJpc3MiOiJodHRwczpcL1wvZGVtby1pcy53ZXN0ZXVyb3BlLmNsb3VkYXBwLmF6dXJlLmNvbVwvb2F1dGgyXC90b2tlbiIsImV4cCI6MTU2OTMyNTI4MCwiaWF0IjoxNTY4NzIwNDgwLCJqdGkiOiI5NjQ4ZGUxOC03MGZkLTQ1NWQtYWNiZC1kMzk5MGZjMzdmYzYifQ.eoRbF17mcQwIH7gE5llKVidr3rDzQ1oDVq27zgghj5gj4cwz0KNWbbIVQ-p_iLzfXfvqwbbuwdCQGBLuNWvREyUfKOL3rNYWtklPwA358tFvvX_QRRmb1C0_IM2hHG8p67fRXFyNhX7wzBoLbf4ZbYtmwi-e7yjIjQWw4-Yiifq89ag9WXUTBxYmTsv4vOni0lC6Tswaml07UERKGNjxXjVB_0Gx2wQZ4zqDjF--jewL2eVHZrLioTV0JpQWRA092UGDY2SLDZk9KoJJJFIO4nk6QK5ONt9wlbSf8hB6ezK91gWq6R2qPGNUMQVZB7l0HdMz8xka_EKj9uUWJLeAvA";

  private static final String url =
      "https://demo-apim.westeurope.cloudapp.azure.com/api_secure/PrecipitationAPI/3.0.0";
  private static final String path = "/weather/precipitation/at";

  @Bean
  public ObjectMapper objectMapper() {
    ObjectMapper objectMapper = new ObjectMapper();
    objectMapper.configure(SerializationFeature.WRITE_DATES_AS_TIMESTAMPS, false);
    objectMapper.registerModule(new JavaTimeModule());
    objectMapper.configure(DeserializationFeature.FAIL_ON_UNKNOWN_PROPERTIES, false);
    return objectMapper;
  }

  @Bean
  public EricssonWeatherClient ericssonWeatherClient(
      ObjectMapper objectMapper, Cache<String, Optional<EricssonWeatherData>> cache) {
    return new EricssonWeatherClient(url, path, objectMapper, cache);
  }

  @Bean
  public Cache<String, Optional<EricssonWeatherData>> weatherDataCache() {
    return CacheBuilder.newBuilder()
        .maximumSize(500)
        .expireAfterWrite(Duration.ofMinutes(10))
        .build();
  }
}
