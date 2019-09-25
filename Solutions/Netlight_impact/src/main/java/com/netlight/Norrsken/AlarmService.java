package com.netlight.Norrsken;

import com.netlight.Norrsken.api.Alarm;
import com.netlight.Norrsken.clients.EricssonWeatherClient;
import com.netlight.Norrsken.clients.domain.EricssonWeatherData;
import com.netlight.Norrsken.domain.AlarmDefinition;
import com.netlight.Norrsken.domain.Area;
import com.netlight.Norrsken.domain.Point;
import com.netlight.Norrsken.domain.ThreasholdAlarm;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.time.OffsetDateTime;
import java.util.Arrays;
import java.util.List;
import java.util.Optional;
import java.util.stream.Collectors;

@Service
public class AlarmService {

  @Autowired EricssonWeatherClient ericssonWeatherClient;

  public List<AlarmDefinition> getDefinitions() {
    return Arrays.asList(threasholdAlarm());
  }

  private AlarmDefinition threasholdAlarm() {
    // 17.906385542168675,59.294137931034484
    //    Point upperLeft = new Point(59.294137931034494, 17.906385542168655);
    //    Point downRight = new Point(59.294137931034474, 17.906385542168685);

    Point upperLeft = new Point(59.1551724137931, 18.435542168674697);
    Point downRight = new Point(59.1551724137931, 18.435542168674697);
    return new AlarmDefinition(
        "https://aCallbackUrl.com", new ThreasholdAlarm(0.0, new Area(upperLeft, downRight)));
  }

  public List<Alarm> getActiveAlarms(OffsetDateTime offsetDateTime, String token) {
    Optional<EricssonWeatherData> weatherData =
        ericssonWeatherClient.getWeatherData(offsetDateTime, token);

    return getDefinitions().stream()
        .map(d -> d.getTrigger().trigger(weatherData))
        .flatMap(List::stream)
        .collect(Collectors.toList());
  }
}
