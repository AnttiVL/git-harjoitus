const scpi_choice_def_t scpi_special_numbers_current[] = {
    {.name = "MAX",       .tag = 0},
    {.name = "MIN",       .tag = 1},
    SCPI_CHOICE_LIST_END,
};


_Bool starts_with(const uint8_t *str, const char *prefix)
{
    size_t len_prefix = strlen(prefix);
    size_t len_str = strlen((const char*)str);

    return (len_str < len_prefix) ? false : strncmp((const char*)str, prefix, len_prefix) == 0;
}


/**
 * *IDN?
 *
 * field1: MANUFACTURE
 * field2: MODEL
 * field4: SUBSYSTEMS REVISIONS
 *
 * example: MANUFACTURE,MODEL,0,01-02-01
 * @param context
 * @return
 */
scpi_result_t SCPI_AI_IDNQ(scpi_t * context)
{
    uint32_t uid[3] = {0, 0, 0};
    utils_get_serial_number(uid);

    txlen = snprintf(txbuf, TXBUFLEN, "\"%s\", \"%s\", \"%08lX%08lX%08lX\", \"%s\"",
                     MANUFACTURER, MODEL, uid[2], uid[1], uid[0], VERSION);
    context->interface->write(context, txbuf, txlen);

    return SCPI_RES_OK;
}


