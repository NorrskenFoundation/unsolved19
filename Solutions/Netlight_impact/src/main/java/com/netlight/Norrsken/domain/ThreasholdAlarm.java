package com.netlight.Norrsken.domain;

import com.netlight.Norrsken.api.Alarm;
import com.netlight.Norrsken.clients.domain.EricssonWeatherData;
import lombok.AllArgsConstructor;
import lombok.Data;

import java.util.Collections;
import java.util.List;
import java.util.Optional;
import java.util.stream.Collectors;

@Data
@AllArgsConstructor
public class ThreasholdAlarm extends Trigger {
  final double threshold;
  final Area area;

  public List<Alarm> trigger(Optional<EricssonWeatherData> weatherData) {
    return weatherData
        .map(
            ericssonWeatherData ->
                ericssonWeatherData.getPoints().stream()
                    .filter(
                        p ->
                            area.surrounds(
                                new Point(
                                    p.getGeometry().getCoordinates()[1],
                                    p.getGeometry().getCoordinates()[0])))
                    .filter(p -> p.getProperties().getValue() > threshold)
                    .map(p -> new Alarm("Over threshold at: " + p.toString(), p))
                    .collect(Collectors.toList()))
        .orElse(Collections.emptyList());
  }
}
