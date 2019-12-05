package com.netlight.Norrsken.api;

import lombok.AllArgsConstructor;
import org.springframework.web.bind.annotation.*;

@RestController
@RequestMapping(value = "/ping")
@AllArgsConstructor
public class PingController {

    @CrossOrigin(origins = "*")
    @GetMapping
    public String ping() {
        return "pong";
    }
}
