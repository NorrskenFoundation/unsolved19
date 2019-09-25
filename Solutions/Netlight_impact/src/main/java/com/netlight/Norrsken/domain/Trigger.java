package com.netlight.Norrsken.domain;

import com.fasterxml.jackson.annotation.JsonSubTypes;
import com.fasterxml.jackson.annotation.JsonTypeInfo;
import com.netlight.Norrsken.api.Alarm;
import com.netlight.Norrsken.clients.domain.EricssonWeatherData;

import java.util.List;
import java.util.Optional;

@JsonTypeInfo(use = JsonTypeInfo.Id.NAME, include = JsonTypeInfo.As.PROPERTY, property = "type")
@JsonSubTypes({@JsonSubTypes.Type(name = "threshold", value = ThreasholdAlarm.class)})
public abstract class Trigger {
  public abstract List<Alarm> trigger(Optional<EricssonWeatherData> weatherData);
}
