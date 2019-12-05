package com.netlight.Norrsken.api;

import com.netlight.Norrsken.Configuration;
import com.netlight.Norrsken.clients.EricssonWeatherClient;
import com.netlight.Norrsken.clients.domain.EricssonWeatherData;
import lombok.AllArgsConstructor;
import org.springframework.web.bind.annotation.*;

import java.time.OffsetDateTime;
import java.util.Collections;
import java.util.Optional;
import java.util.stream.Collectors;

@RestController
@RequestMapping(value = "/api")
@AllArgsConstructor
public class WeatherController {
  EricssonWeatherClient ericssonWeatherClient;

  @CrossOrigin(origins = "*")
  @RequestMapping(
      value = "/weather",
      method = RequestMethod.GET,
      produces = {"application/json"})
  public Weather getWeatherData(@RequestParam("time") String timeString) {
    OffsetDateTime time = OffsetDateTime.parse(timeString);
    Optional<EricssonWeatherData> stockholm =
        ericssonWeatherClient.getWeatherData(time, Configuration.TOKEN);
    return new Weather(
        stockholm
            .map(
                s ->
                    s.getPoints().stream()
                        .map(
                            p ->
                                new Point(
                                    p.getGeometry().getCoordinates()[0],
                                    p.getGeometry().getCoordinates()[1],
                                    p.getProperties().getValue()))
                        .collect(Collectors.toList()))
            .orElse(Collections.emptyList()));
  }
}
